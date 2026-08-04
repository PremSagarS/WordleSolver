from data import load_data, loadDict, loadMatrix, FNAME
from match import encode, MatchType, decodeFromUserInput
from math import log2

matrix = loadMatrix()
rescache = loadDict()
words = load_data(FNAME)
invalids = set()

def entropy(idx: int) -> float:
    bins = rescache[idx]
    denom = sum(bins)
    retval = 0

    for bin in bins:
        if bin == 0: continue
        retval += -1 * (bin / denom) * log2(bin / denom)
    
    return retval

def bestGuess() -> list[tuple[int, str]]:
    values = []
    for idx, word in enumerate(words):
        if idx in invalids:
            continue
        values.append(((idx, word), entropy(idx)))

    values = sorted(values, key=lambda x: x[1], reverse=True)
    best_score = values[0][1]

    return [item[0] for item in values if item[1] == best_score]


def adjust(guess: tuple[int, str], matchResult: list[MatchType]):
    matchResult = encode(matchResult)
    row = matrix[guess[0]]

    for residx, res in enumerate(row):
        if residx in invalids:
            continue
        if encode(res) != matchResult:
            invalids.add(residx)
            for widx in range(len(words)):
                rescache[widx][encode(matrix[widx][residx])] -= 1
    


for i in range(6):
    bg = bestGuess()
    print(bg)
    adjust((int(input()), input()), decodeFromUserInput(input().strip()))