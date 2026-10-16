#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"

echo "🔄 Checking for updates..."
git fetch

LOCAL=$(git rev-parse HEAD)
REMOTE=$(git rev-parse @{u})

if [ "$LOCAL" = "$REMOTE" ]; then
    echo "✅ Already up to date."
    exit 0
fi

echo "📥 Updates available. Pulling..."
git pull

echo "🔨 Rebuilding..."
./build.sh

echo "✅ Updated successfully!"
