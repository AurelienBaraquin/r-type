#!/bin/bash

if [ "$1" = "-n" ] && [ -n "$2" ]; then
   filename="$2.lua"

   cat > "$filename" << EOF

self = nil

function init(e)
   self = e
end

function update(delta)

end
EOF

   echo "Created Lua script: $filename"
else
   echo "Usage: $0 -n <script_name>"
fi