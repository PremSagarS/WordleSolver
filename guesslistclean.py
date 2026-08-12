# GPT SHIT

"""
rearrange.py

Reads A.txt (read-only) and B.txt (a superset of A.txt, possibly with extra
lines and/or duplicates), and writes out a rearranged version of B where:
  1. Every line from A.txt appears first, in the exact order they appear in A.txt.
  2. All remaining lines of B.txt (the ones not "used up" by A.txt) follow,
     in their original relative order from B.txt.

Handles duplicate lines correctly: if a line appears multiple times in A.txt,
it will consume that many matching occurrences from B.txt (using each B line
only once).

Usage:
    python rearrange.py A.txt B.txt output.txt
"""

import sys
from collections import deque, defaultdict


def read_lines(path):
    with open(path, "r", encoding="utf-8") as f:
        # keepends=False so we control newline joining ourselves;
        # this also means trailing-newline differences don't cause mismatches.
        return [line.rstrip("\n") for line in f]


def rearrange(a_lines, b_lines):
    # Map each distinct line -> queue of indices in B where it occurs.
    positions = defaultdict(deque)
    for idx, line in enumerate(b_lines):
        positions[line].append(idx)

    used = [False] * len(b_lines)
    front_part = []

    for line in a_lines:
        if line in positions and positions[line]:
            idx = positions[line].popleft()
            used[idx] = True
            front_part.append(b_lines[idx])
        else:
            # A.txt line has no remaining match in B.txt.
            raise ValueError(
                f"Line from A.txt not found (or exhausted) in B.txt: {line!r}"
            )

    remaining_part = [b_lines[i] for i in range(len(b_lines)) if not used[i]]

    return front_part + remaining_part


def main():
    if len(sys.argv) != 4:
        print("Usage: python rearrange.py A.txt B.txt output.txt")
        sys.exit(1)

    a_path, b_path, out_path = sys.argv[1], sys.argv[2], sys.argv[3]

    a_lines = read_lines(a_path)
    b_lines = read_lines(b_path)

    result = rearrange(a_lines, b_lines)

    with open(out_path, "w", encoding="utf-8") as f:
        for line in result:
            f.write(line + "\n")

    print(f"Wrote {len(result)} lines to {out_path}")


if __name__ == "__main__":
    main()