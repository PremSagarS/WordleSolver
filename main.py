from collections import Counter
from math import log2

from data import load_data, loadMatrix, FNAME
from match import encode

MAX_GUESSES = 6
HARD_CAP = 15

words = load_data(FNAME)
n = len(words)

raw_matrix = loadMatrix()
encoded = [[encode(raw_matrix[i][j]) for j in range(n)] for i in range(n)]

guess_cache: dict[frozenset, int] = {}


def entropy_of(guess_idx: int, candidates: list[int]) -> float:
    bins = [0] * 243
    row = encoded[guess_idx]
    for c in candidates:
        bins[row[c]] += 1

    denom = len(candidates)
    result = 0.0
    for count in bins:
        if count == 0:
            continue
        p = count / denom
        result += -p * log2(p)
    return result


def best_guess(candidate_set: frozenset) -> int:
    cached = guess_cache.get(candidate_set)
    if cached is not None:
        return cached

    candidates = sorted(candidate_set)
    best_idx = candidates[0]
    best_key = (-1.0, False)
    for idx in range(n):
        score = entropy_of(idx, candidates)
        key = (score, idx in candidate_set)
        if key > best_key:
            best_key = key
            best_idx = idx

    guess_cache[candidate_set] = best_idx
    return best_idx


def solve(answer_idx: int) -> int:
    candidates = frozenset(range(n))

    for guess_count in range(1, HARD_CAP + 1):
        guess_idx = best_guess(candidates)

        if guess_idx == answer_idx:
            return guess_count

        result = encoded[guess_idx][answer_idx]
        candidates = frozenset(
            c for c in candidates if encoded[guess_idx][c] == result
        )

    return HARD_CAP + 1


def print_histogram(histogram: Counter, width: int = 50) -> None:
    max_count = max(histogram.values())
    for guesses in range(1, max(histogram.keys()) + 1):
        count = histogram.get(guesses, 0)
        bar_len = round(width * count / max_count) if max_count else 0
        bar = "#" * bar_len
        label = f"{guesses:>2}" if guesses <= MAX_GUESSES else f"{guesses:>2}+"
        print(f"{label} | {bar} {count}")


def main() -> None:
    histogram: Counter = Counter()
    total_guesses = 0
    failures = []

    for answer_idx, answer_word in enumerate(words):
        guesses = solve(answer_idx)
        histogram[guesses] += 1
        total_guesses += guesses
        if guesses > MAX_GUESSES:
            failures.append((answer_word, guesses))

        if (answer_idx + 1) % 200 == 0:
            print(f"{answer_idx + 1}/{n}")

    print()
    print(f"words: {n} , avg: {total_guesses / n:.3f}, caches: {len(guess_cache)}")
    print(f"fails: {len(failures)}")
    print()

    print_histogram(histogram)


if __name__ == "__main__":
    main()