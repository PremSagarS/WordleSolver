from match import MatchType
from collections import Counter

def twoWordMatch(guess: str, answer: str) -> list[MatchType]:
    assert len(guess) == len(answer) == 5
    retval = [MatchType.GREY for i in range(5)]

    ansDict = Counter(answer)

    for i in range(5):
        if guess[i] == answer[i]:
            ansDict[guess[i]] -= 1
            retval[i] = MatchType.GREEN
    
    for i in range(5):
        if retval[i] == MatchType.GREEN: continue
        if ansDict.get(guess[i], 0) == 0: continue
        ansDict[guess[i]] -= 1
        retval[i] = MatchType.YELLOW

    return retval

if __name__ == "__main__":
    print(twoWordMatch("crane", "grain"))