# /// script
# requires-python = ">=3.9"
# dependencies = [
#   "plotly",
# ]
# ///

import csv
from collections import defaultdict
from pathlib import Path

import plotly.graph_objects as go


def load_results(filename):
    """Read benchmark rows from a CSV file.

    >>> rows = load_results("bench.csv")
    >>> rows[0]["container"]
    'list'
    """
    with open(filename, newline="", encoding="utf-8") as csvfile:
        rows = list(csv.DictReader(csvfile))

    required = {"container", "operation", "size", "iterations", "ns_per_operation"}
    if not rows or not required.issubset(rows[0]):
        raise ValueError("CSV must contain the required benchmark columns")

    for row in rows:
        row["size"] = int(row["size"])
        row["iterations"] = int(row["iterations"])
        row["ns_per_operation"] = float(row["ns_per_operation"])

    return rows


def build_chart(rows):
    """Create an interactive Plotly chart from benchmark rows.

    >>> fig = build_chart([{
    ...     "container": "vector",
    ...     "operation": "at",
    ...     "size": 10,
    ...     "iterations": 1,
    ...     "ns_per_operation": 2.5,
    ... }])
    >>> len(fig.data)
    1
    """
    groups = defaultdict(list)
    for row in rows:
        groups[(row["operation"], row["container"])].append(row)

    operations = sorted({row["operation"] for row in rows})
    containers = sorted({row["container"] for row in rows})
    fig = go.Figure()
    operation_traces = defaultdict(list)

    for operation in operations:
        for container in containers:
            points = sorted(
                groups.get((operation, container), []),
                key=lambda row: row["size"],
            )
            if not points:
                continue

            trace_index = len(fig.data)
            operation_traces[operation].append(trace_index)
            fig.add_trace(
                go.Scatter(
                    x=[row["size"] for row in points],
                    y=[row["ns_per_operation"] for row in points],
                    mode="lines+markers",
                    name=container,
                    legendgroup=container,
                    visible=(operation == operations[0]),
                    customdata=[row["iterations"] for row in points],
                    hovertemplate=(
                        "Container: %{fullData.name}<br>"
                        "Size: %{x}<br>"
                        "ns/operation: %{y}<br>"
                        "Iterations: %{customdata}<extra></extra>"
                    ),
                )
            )

    buttons = []
    for operation in operations:
        visible = [False] * len(fig.data)
        for index in operation_traces[operation]:
            visible[index] = True

        buttons.append(
            {
                "label": operation,
                "method": "update",
                "args": [
                    {"visible": visible},
                    {"title": f"{operation}: benchmark time by input size"},
                ],
            }
        )

    fig.update_layout(
        title=f"{operations[0]}: benchmark time by input size",
        xaxis_title="Input size",
        yaxis_title="Nanoseconds per operation",
        xaxis_type="log",
        yaxis_type="log",
        template="plotly_white",
        updatemenus=[
            {
                "buttons": buttons,
                "direction": "down",
                "showactive": True,
                "x": 0,
                "xanchor": "left",
                "y": 1.15,
                "yanchor": "top",
            }
        ],
        margin={"t": 110},
    )

    return fig


def main():
    rows = load_results("bench.csv")
    fig = build_chart(rows)
    fig.write_html(
        "benchmark.html",
        full_html=True,
        include_plotlyjs=True,
    )
    print(f"Wrote {Path('benchmark.html').resolve()}")


if __name__ == "__main__":
    main()
