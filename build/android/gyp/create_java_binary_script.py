#!/usr/bin/env python
#
# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Creates a simple script to run a java "binary".

This creates a script that sets up the java command line for running a java
jar. This includes correctly setting the classpath and the main class.
"""

import optparse
import os
import sys

from util import build_utils

# The java command must be executed in the current directory because there may
# be user-supplied paths in the args. The script receives the classpath relative
# to the directory that the script is written in and then, when run, must
# recalculate the paths relative to the current directory.
script_template = """\
#!/usr/bin/env python
#
# This file was generated by build/android/gyp/create_java_binary_script.py

import argparse
import os
import sys

self_dir = os.path.dirname(__file__)
classpath = [{classpath}]
bootclasspath = [{bootclasspath}]
extra_program_args = {extra_program_args}
if os.getcwd() != self_dir:
  offset = os.path.relpath(self_dir, os.getcwd())
  classpath = [os.path.join(offset, p) for p in classpath]
  bootclasspath = [os.path.join(offset, p) for p in bootclasspath]
java_cmd = ["java"]
# This is a simple argparser for jvm and jar arguments.
parser = argparse.ArgumentParser()
parser.add_argument('--jar-args')
parser.add_argument('--jvm-args')

known_args, unknown_args = parser.parse_known_args(sys.argv[1:])
if known_args.jvm_args:
  jvm_arguments = known_args.jvm_args.strip('"').split()
  java_cmd.extend(jvm_arguments)
if known_args.jar_args:
  jar_arguments = known_args.jar_args.strip('"').split()
  if unknown_args:
    raise Exception('There are unknown arguments')
else:
  jar_arguments = unknown_args

{noverify_flag}
if bootclasspath:
    java_cmd.append("-Xbootclasspath/p:" + ":".join(bootclasspath))
java_cmd.extend(
    ["-classpath", ":".join(classpath), "-enableassertions", \"{main_class}\"])
java_cmd.extend(extra_program_args)
java_cmd.extend(jar_arguments)
os.execvp("java", java_cmd)
"""

def main(argv):
  argv = build_utils.ExpandFileArgs(argv)
  parser = optparse.OptionParser()
  build_utils.AddDepfileOption(parser)
  parser.add_option('--output', help='Output path for executable script.')
  parser.add_option('--main-class',
      help='Name of the java class with the "main" entry point.')
  parser.add_option('--classpath', action='append', default=[],
      help='Classpath for running the jar.')
  parser.add_option('--bootclasspath', action='append', default=[],
      help='zip/jar files to add to bootclasspath for java cmd.')
  parser.add_option('--noverify', action='store_true',
      help='JVM flag: noverify.')

  options, extra_program_args = parser.parse_args(argv)

  if (options.noverify):
    noverify_flag = 'java_cmd.append("-noverify")'
  else:
    noverify_flag = ''

  classpath = []
  for cp_arg in options.classpath:
    classpath += build_utils.ParseGnList(cp_arg)

  bootclasspath = []
  for bootcp_arg in options.bootclasspath:
    bootclasspath += build_utils.ParseGnList(bootcp_arg)

  run_dir = os.path.dirname(options.output)
  bootclasspath = [os.path.relpath(p, run_dir) for p in bootclasspath]
  classpath = [os.path.relpath(p, run_dir) for p in classpath]

  with open(options.output, 'w') as script:
    script.write(script_template.format(
      classpath=('"%s"' % '", "'.join(classpath)),
      bootclasspath=('"%s"' % '", "'.join(bootclasspath)
                     if bootclasspath else ''),
      main_class=options.main_class,
      extra_program_args=repr(extra_program_args),
      noverify_flag=noverify_flag))

  os.chmod(options.output, 0750)

  if options.depfile:
    build_utils.WriteDepfile(options.depfile, options.output)


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
