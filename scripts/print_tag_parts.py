#!/usr/bin/env python
from __future__ import with_statement
from pprint import pprint
import sys


def get_parts(data):
    parts = []
    start = 0
    for i in range(len(data)):
        if data[i] == '<':
            parts.append(data[start:i])
            start = i

    return parts


if __name__ == "__main__":
    if len(sys.argv) > 1:
        with open(sys.argv[1], 'r') as fh:
            data = fh.read()
    else:
        data = sys.stdin.read()

    parts = get_parts(data)
    pprint(parts)

