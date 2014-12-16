# root log directory-/var/log
LOG_DIR=/var/log

# better variable than solid code
cd $LOG_DIR

cat /dev/null > messages
cat /dev/null > wtmp

echo "Logs cleaned up."

# normal exit sheel runtime.
exit

