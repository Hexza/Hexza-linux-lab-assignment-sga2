# Question 4: Real-Time Error Log Monitor

## Command 1
```bash
touch application.log
```
**Explanation:** Created the log file that the monitor will watch for new entries.

![screenshot](Screenshots/1-touch-log.png)

## Command 2
```bash
tail -f application.log 2>/dev/null | grep --line-buffered "ERROR" | tee -a error_report.txt
```
**Explanation:** Started a live pipeline that watches the log file, filters only ERROR lines, and appends them to error_report.txt.

![screenshot](Screenshots/2-pipeline-waiting.png)

## Command 3
```bash
echo "INFO: Server started" >> application.log
echo "ERROR: Database connection timeout" >> application.log
echo "WARNING: High memory usage" >> application.log
echo "ERROR: Failed to write to disk" >> application.log
```
**Explanation:** Added mixed log messages so the pipeline could demonstrate that only ERROR entries are captured.

![screenshot](Screenshots/3-feed-logs.png)

**Explanation:** The running pipeline displayed the two ERROR messages live after they were written to the log file.

![screenshot](Screenshots/4-errors-captured.png)

## Command 4
```bash
cat error_report.txt
```
**Explanation:** Verified that only the two ERROR messages were saved into the report file.

![screenshot](Screenshots/5-error-report.png)
