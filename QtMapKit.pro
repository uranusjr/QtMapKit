TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = src demo
demo.depends = src
