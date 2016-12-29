# Skip shell-style commenting
/#\(.*\)/b

s/PROJECT_NAME\(\s*\)=\(.*\)//
s/INPUT\(\s*\)=\(.*\)//
s/FILE_PATTERNS\(\s*\)=\(.*\)//
s/RECURSIVE\(\s*\)=\(.*\)//
s/WARN_LOGFILE\(\s*\)=\(.*\)//
s/HHC_LOCATION\(\s*\)=\(.*\)//
s/CHM_FILE\(\s*\)=\(.*\)//

