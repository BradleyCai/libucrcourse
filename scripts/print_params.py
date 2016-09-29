#!/usr/bin/env python2
from __future__ import with_statement
from pprint import pprint
import sys
import urllib

def unescape(string):
    return urllib.unquote(string)

def get_params(fh):
    data = fh.read()
    fh.close()

    params = {}
    for arg in data.split('&'):
        key, value = arg.split('=')
        params[unescape(key)] = unescape(value)

    return params

if __name__ == "__main__":
    if len(sys.argv) > 1:
        params = get_params(open(sys.argv[1], 'r'))
    else:
        params = get_params(sys.stdin)

    if len(sys.argv) > 2:
        params2 = get_params(open(sys.argv[2], 'r'))
    else:
        params2 = None

    if params2 is None:
        pprint(params)
    else:
        keys = params.keys() + params2.keys()
        for key in keys:
            if key not in params.viewkeys():
                print("+ %s -> %r" % (key, params2[key]))
            elif key not in params2.viewkeys():
                print("- %s -> %r" % (key, params[key]))
            elif params[key] != params2[key]:
                print("~ %s ->\n  %r\n  %r" % (key, params[key], params2[key]))

