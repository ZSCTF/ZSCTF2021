#!/bin/bash

# Secure entrypoint
chmod 600 /entrypoint.sh

mv /flag /flag

exec "$@"
