#!/usr/bin/env bash

set -eux
cpplint --root=src "$(pwd)"/src/**/*.{cpp,h}
