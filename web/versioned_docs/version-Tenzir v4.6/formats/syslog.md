# syslog

Reads syslog messages.

## Synopsis

```
syslog
```

## Description

Syslog is a standard format for message logging.
Tenzir supports reading syslog messages in both the standardized "Syslog Protocol" format
([RFC 5424](https://tools.ietf.org/html/rfc5424)), and the older "BSD syslog Protocol" format
([RFC 3164](https://tools.ietf.org/html/rfc3164)).

Depending on the syslog format, the result can be different.
Here's an example of a syslog message in RFC 5424 format:

```
<165>8 2023-10-11T22:14:15.003Z mymachineexamplecom evntslog 1370 ID47 [exampleSDID@32473 eventSource="Application" eventID="1011"] Event log entry
```

With this input, the parser will produce the following output, with the schema name `syslog.rfc5424`:

```json
{
  "facility": 20,
  "severity": 5,
  "version": 8,
  "timestamp": "2023-10-11T22:14:15.003000",
  "hostname": "mymachineexamplecom",
  "app_name": "evntslog",
  "process_id": "1370",
  "message_id": "ID47",
  "message": "Event log entry"
}
```

:::note Structured Data
The STRUCTURED-DATA field defined in RFC 5424, delimited by square brackets `[]` in the input,
is currently not included in the resulting schema.
:::

Here's an example of a syslog message in RFC 3164 format:

```
<34> Nov 16 14:55:56 mymachine PROGRAM: Freeform message
```

With this input, the parser will produce the following output, with the schema name `syslog.rfc3164`:

```json
{
  "facility": 4,
  "severity": 2,
  "timestamp": "Nov 16 14:55:56",
  "hostname": "mymachine",
  "tag": "PROGRAM",
  "content": "Freeform message"
}
```

## Examples

Read a syslog file:

```
from mylog.log read syslog
```
