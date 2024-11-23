#!/bin/bash

# Paths
PHILO_EXEC="./philo" # Remplace par le chemin de ton exécutable
LOG_FILE="tester.log"

# Utility function to log results
log() {
    echo -e "$1" >> $LOG_FILE
    echo -e "$1"
}

# Test 1: Invalid arguments
log "\n== Test 1: Invalid arguments =="
$PHILO_EXEC 4 -1 100 100 > /dev/null 2>&1 && log "FAIL: Accepted negative time_to_die" || log "PASS: Rejected negative time_to_die"
$PHILO_EXEC 4 100 abc 100 > /dev/null 2>&1 && log "FAIL: Accepted non-numeric input" || log "PASS: Rejected non-numeric input"
$PHILO_EXEC > /dev/null 2>&1 && log "FAIL: Accepted no arguments" || log "PASS: Rejected no arguments"

# Test 2: Single philosopher
log "\n== Test 2: Single philosopher =="
$PHILO_EXEC 1 200 100 100 > single.log &
sleep 1
pkill philo
grep "has taken a fork" single.log && log "PASS: Single philosopher behavior is correct" || log "FAIL: Single philosopher behavior is incorrect"

# Test 3: Starvation scenario
log "\n== Test 3: Starvation scenario =="
$PHILO_EXEC 5 800 200 200 > starvation.log &
sleep 5
pkill philo
grep "died" starvation.log && log "PASS: Detected starvation" || log "FAIL: Starvation not detected"

# Test 4: High philosopher count
log "\n== Test 4: High philosopher count =="
$PHILO_EXEC 100 800 200 200 > /dev/null 2>&1 && log "PASS: High philosopher count handled" || log "FAIL: Crash on high philosopher count"

# Test 5: Performance check
log "\n== Test 5: Performance under load =="
$PHILO_EXEC 50 2000 300 300 > /dev/null 2>&1 &
pid=$!
sleep 3
kill -0 $pid > /dev/null 2>&1 && log "PASS: Performance is stable" || log "FAIL: Performance issue detected"
kill -9 $pid

# Test 6: Valgrind memory check
log "\n== Test 6: Memory leaks =="
if command -v valgrind &> /dev/null
then
    valgrind --leak-check=full --error-exitcode=1 $PHILO_EXEC 4 800 200 200 > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        log "PASS: No memory leaks detected"
    else
        log "FAIL: Memory leaks detected"
    fi
else
    log "SKIP: Valgrind not installed"
fi
