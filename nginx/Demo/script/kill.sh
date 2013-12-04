#!/usr/bin/bash

ps aux | grep demo | grep -v "grep" | awk '{print $2}' | xargs -i kill -9 {}
