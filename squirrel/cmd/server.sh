#!/bin/bash
nohup node ../source/server.js 3000 >> ../logs/3000.log &
nohup node ../source/server.js 3001 >> ../logs/3000.log &
nohup node ../source/server.js 3002 >> ../logs/3000.log &
