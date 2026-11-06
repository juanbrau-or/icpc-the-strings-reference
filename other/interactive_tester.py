# Python 3. Local judge for guessing an integer in [1, 1000000].
# Query: an integer k; reply: ">=" if secret >= k, otherwise "<".
# Answer: ! x. At most 25 queries. Adapt to the actual problem protocol.
import argparse
import queue
import random
import subprocess
import threading


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("solution", nargs="?", default="./a.out")
    parser.add_argument("--seed", type=int, default=712367821)
    args = parser.parse_args()
    secret = random.Random(args.seed).randint(1, 1000000)
    p = subprocess.Popen([args.solution], stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE, text=True, bufsize=1)
    lines = queue.Queue()

    def reader():
        for line in p.stdout:
            lines.put(line)
        lines.put(None)

    threading.Thread(target=reader, daemon=True).start()
    queries = 0
    try:
        while True:
            line = lines.get(timeout=5)
            assert line is not None, "solution exited without an answer"
            tokens = line.split()
            assert tokens, "empty query"
            if tokens[0] == "!":
                assert len(tokens) == 2 and int(tokens[1]) == secret, "wrong answer"
                print(f"OK seed={args.seed}, queries={queries}")
                break
            assert len(tokens) == 1 and queries < 25, "invalid query / query limit"
            k = int(tokens[0])
            assert 1 <= k <= 1000000, "query out of range"
            p.stdin.write(">=\n" if secret >= k else "<\n")
            p.stdin.flush()
            queries += 1
    except Exception:
        print(f"FAILED seed={args.seed}")
        raise
    finally:
        if p.poll() is None:
            p.kill()
        p.wait()
        p.stdin.close()
        p.stdout.close()


if __name__ == "__main__":
    main()
