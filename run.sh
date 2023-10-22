#!/bin/bash

export PATH=$PATH:/mnt/c/DEV/arnold_sdk/Arnold-7.2.4.1-linux/bin
export ARNOLD_PLUGIN_PATH=/mnt/c/DEV/arnold_shaders_dev/build/:ARNOLD_PLUGIN_PATH

kick -sl -v 6 -sr 2 -l ARNOLD_PLUGIN_PATH test_scenes/simple_scene.ass
