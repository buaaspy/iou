#!/usr/bin/bash

ps aux | grep nginx | awk '{print $2}' | xargs -i kill -9 {}