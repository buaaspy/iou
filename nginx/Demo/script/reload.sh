#!/usr/bin/bash

ps aux | grep nginx | grep master | awk '{print $2}' | xargs -i kill -HUP {}