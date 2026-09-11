import subprocess
import json
import random
import sys
from pathlib import Path
import plotly.graph_objects as go
from plotly.subplots import make_subplots

SIZES = [1, 2, 4, 10, 100, 1000, 10000, 100000]

COLOR_MAP = {
    "bubble": "#1f77b4",
    "selection": "#ff7f0e"
}

def compile_algorithms():
    algo_dir = Path("algorithms")
    bin_dir = Path("bin")
    bin_dir.mkdir(exist_ok=True)
    
    results = {}
    if not algo_dir.exists():
        return results

    for cpp_file in algo_dir.glob("*.cc"):
        name = cpp_file.stem
        bin_path = bin_dir / name
        print(f"Compiling {cpp_file}...", file=sys.stderr)
        res = subprocess.run(["g++", "-std=c++23", "-O3", str(cpp_file), "-o", str(bin_path)], capture_output=True, text=True)
        if res.returncode != 0:
            print(f"Compilation failed for {name}:\n{res.stderr}", file=sys.stderr)
            continue
        
        algo_data = {
            "random": {"sizes": [], "times": [], "comparisons": []},
            "presorted": {"sizes": [], "times": [], "comparisons": []},
            "reversesorted": {"sizes": [], "times": [], "comparisons": []}
        }

        for mode in ["random", "presorted", "reversesorted"]:
            for size in SIZES:
                print(f"Testing {bin_path} for {size} {mode}")
                if mode == "random":
                    lst = [random.randint(0, 1000000) for _ in range(size)]
                elif mode == "presorted":
                    lst = list(range(size))
                else:
                    lst = list(range(size, 0, -1))

                input_str = "\n".join(map(str, lst)) + "\n"
                try:
                    run_res = subprocess.run([str(bin_path)], input=input_str, capture_output=True, text=True, timeout=60)
                    if run_res.returncode != 0:
                        print(f"Runtime error for {name} at size {size} ({mode}): {run_res.stderr}", file=sys.stderr)
                        break
                    
                    output_lines = run_res.stdout.strip().split("\n")
                    sorted_elements = []
                    comp_val = 0
                    time_val = 0.0
                    for line in output_lines:
                        if line.startswith("Comparisons:"):
                            comp_val = int(line.split(":")[1].strip())
                        elif line.startswith("Time:"):
                            time_val = float(line.split(":")[1].replace("seconds", "").strip())
                        elif line.strip():
                            # The sorted array might be printed as space-separated tokens on a line
                            tokens = line.strip().split()
                            if tokens:
                                try:
                                    sorted_elements = [int(t) for t in tokens]
                                except ValueError:
                                    pass

                    if sorted_elements != sorted(lst):
                        print(f"Error: Output not correctly sorted for {name} at size {size} ({mode})!", file=sys.stderr)
                        print(f"Expected sorted list of length {len(lst)}, got {sorted_elements[:10]}...", file=sys.stderr)
                        sys.exit(1)

                    algo_data[mode]["sizes"].append(size)
                    algo_data[mode]["times"].append(time_val)
                    algo_data[mode]["comparisons"].append(comp_val)
                except subprocess.TimeoutExpired:
                    print(f"Timeout for {name} at size {size} ({mode})", file=sys.stderr)
                    break

        results[name] = algo_data

    return results

def generate_dashboard(data):
    fig = make_subplots(
        rows=3, cols=2,
        subplot_titles=(
            "Random - Time (s)", "Random - Comparisons",
            "Presorted - Time (s)", "Presorted - Comparisons",
            "Reverse-Sorted - Time (s)", "Reverse-Sorted - Comparisons"
        )
    )

    modes = [("random", 1), ("presorted", 2), ("reversesorted", 3)]
    
    # Track added legend items to avoid duplicate legend entries when toggling together
    legend_groups_added = set()

    for algo_name, algo_data in data.items():
        color = COLOR_MAP.get(algo_name, "#2ca02c")
        for mode, row in modes:
            m_data = algo_data[mode]
            if not m_data["sizes"]:
                continue
            
            # Show legend only on the very first trace for this algorithm overall
            show_legend = algo_name not in legend_groups_added
            
            # Time trace (col 1)
            fig.add_trace(
                go.Scatter(
                    x=m_data["sizes"],
                    y=m_data["times"],
                    mode='lines+markers',
                    name=algo_name,
                    legendgroup=algo_name,
                    showlegend=show_legend,
                    marker=dict(color=color),
                    line=dict(color=color)
                ),
                row=row, col=1
            )
            # Mark legend_groups_added after the first trace is added so subsequent traces for this algorithm have showlegend=False
            legend_groups_added.add(algo_name)

            # Comparisons trace (col 2)
            fig.add_trace(
                go.Scatter(
                    x=m_data["sizes"],
                    y=m_data["comparisons"],
                    mode='lines+markers',
                    name=algo_name,
                    legendgroup=algo_name,
                    showlegend=False,
                    marker=dict(color=color),
                    line=dict(color=color)
                ),
                row=row, col=2
            )

    fig.update_xaxes(type="linear", title_text="Input Size (N)")
    fig.update_yaxes(type="linear", title_text="Time (s)", row=1, col=1)
    fig.update_yaxes(type="linear", title_text="Comparisons", row=1, col=2)
    fig.update_yaxes(type="linear", title_text="Time (s)", row=2, col=1)
    fig.update_yaxes(type="linear", title_text="Comparisons", row=2, col=2)
    fig.update_yaxes(type="linear", title_text="Time (s)", row=3, col=1)
    fig.update_yaxes(type="linear", title_text="Comparisons", row=3, col=2)

    fig.update_layout(
        template="plotly_white",
        margin=dict(l=40, r=40, t=60, b=40),
        height=900,
        updatemenus=[
            dict(
                type="buttons",
                direction="right",
                x=0.5,
                y=1.12,
                xanchor="center",
                yanchor="top",
                buttons=[
                    dict(
                        label="Linear Scale",
                        method="relayout",
                        args=[
                            {
                                "xaxis.type": "linear", "xaxis2.type": "linear", "xaxis3.type": "linear",
                                "xaxis4.type": "linear", "xaxis5.type": "linear", "xaxis6.type": "linear",
                                "yaxis.type": "linear", "yaxis2.type": "linear", "yaxis3.type": "linear",
                                "yaxis4.type": "linear", "yaxis5.type": "linear", "yaxis6.type": "linear"
                            }
                        ]
                    ),
                    dict(
                        label="Log-Log Scale",
                        method="relayout",
                        args=[
                            {
                                "xaxis.type": "log", "xaxis2.type": "log", "xaxis3.type": "log",
                                "xaxis4.type": "log", "xaxis5.type": "log", "xaxis6.type": "log",
                                "yaxis.type": "log", "yaxis2.type": "log", "yaxis3.type": "log",
                                "yaxis4.type": "log", "yaxis5.type": "log", "yaxis6.type": "log"
                            }
                        ]
                    ),
                ]
            )
        ]
    )

    html_content = fig.to_html(full_html=True, include_plotlyjs='cdn')
    Path("index.html").write_text(html_content)

if __name__ == "__main__":
    data = compile_algorithms()
    generate_dashboard(data)
