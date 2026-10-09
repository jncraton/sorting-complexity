import argparse
import doctest
import re
import sys


def skip_noncode(text, index):
    """
    >>> skip_noncode("a // note\\nb", 2)
    10
    >>> skip_noncode('a "b" c', 2)
    5
    """
    if text.startswith("//", index):
        end = text.find("\n", index + 2)
        return len(text) if end == -1 else end + 1
    if text.startswith("/*", index):
        end = text.find("*/", index + 2)
        return len(text) if end == -1 else end + 2
    if text[index] in ("'", '"'):
        quote = text[index]
        index += 1
        while index < len(text):
            if text[index] == "\\":
                index += 2
            elif text[index] == quote:
                return index + 1
            else:
                index += 1
        return len(text)
    return index


def matching_brace(text, start):
    """
    >>> matching_brace("{ a { b } c }", 0)
    12
    """
    depth = 0
    index = start
    while index < len(text):
        skipped = skip_noncode(text, index)
        if skipped != index:
            index = skipped
            continue
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return index
        index += 1
    raise ValueError("unmatched opening brace")


def convert(text):
    """
    >>> convert("template <typename T> void A<T>::f() { work(); }")
    'template <typename T> void A<T>::f() { throw "unimplemented"; }'
    """
    stub = '{ throw "unimplemented"; }'
    replacements = []
    boundary = 0
    index = 0

    while index < len(text):
        skipped = skip_noncode(text, index)
        if skipped != index:
            index = skipped
            continue

        char = text[index]

        if char in ";}":
            boundary = index + 1
        elif char == "{":
            prefix = text[boundary:index]
            is_method = re.search(
                r"(?:\b[A-Za-z_]\w*\s*(?:<[^{};]*>)?\s*::\s*)+" r"~?[A-Za-z_]\w*\s*\(",
                prefix,
            )
            ends_like_signature = re.search(
                r"\)\s*(?:const\s*)?"
                r"(?:noexcept(?:\s*\([^)]*\))?\s*)?"
                r"(?:&\s*)?$",
                prefix,
            )

            if is_method and ends_like_signature:
                end = matching_brace(text, index)
                replacements.append((index, end + 1))
                index = end + 1
                boundary = index
                continue

            boundary = index + 1

        index += 1

    for start, end in reversed(replacements):
        text = text[:start] + stub + text[end:]

    return text


def main():
    """
    >>> callable(main)
    True
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("input")
    parser.add_argument("output", nargs="?")
    args = parser.parse_args()

    with open(args.input, encoding="utf-8") as source:
        result = convert(source.read())

    if args.output:
        with open(args.output, "w", encoding="utf-8") as destination:
            destination.write(result)
    else:
        sys.stdout.write(result)


if __name__ == "__main__":
    if "--test" in sys.argv:
        sys.argv.remove("--test")
        doctest.testmod()
    else:
        main()
