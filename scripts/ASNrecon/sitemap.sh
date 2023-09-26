#!/bin/bash

if ! command -v xmlstarlet &> /dev/null; then
  echo "xmlstartlet not installed"
  exit 1
fi

if ! command -v curl &> /dev/null; then
  echo "curl not installed"
  exit 1
fi

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <sitemap_url>"
  exit 1
fi

SITEMAP_URL="$1"
TEMP_FILE="temp_sitemap.xml"

curl -s "$SITEMAP_URL" -o "$TEMP_FILE"

xmlstarlet sel -t -v "//loc" "$TEMP_FILE"

rm "$TEMP_FILE"
