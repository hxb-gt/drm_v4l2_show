#!/bin/bash

automake
autoconf
make DESTDIR=/home/hxb/works/opensource_package/drm_v4l2_show/install install
