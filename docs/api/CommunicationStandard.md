# Communication Standard for WebSocket-Based Control Plane and Agents

## Overview
This document defines the communication standard between the **Control Plane** and **Agents** using **WebSockets** with structured **JSON messages**. The communication is **bidirectional**, allowing both entities to send and receive messages efficiently.

## Message Format
Each message exchanged between the control plane and an agent must adhere to the following JSON structure:

```json
{
  "type": "<message_type>",
  "request_id": "<unique_request_id>",
  "timestamp": "<ISO_8601_UTC>",
  "payload": { <message_specific_data> }
}
```

### Fields Explanation
| Field       | Type   | Required | Description |
|------------|--------|----------|-------------|
| `type`      | String | ✅ Yes  | The type of message (e.g., `command`, `status_update`, `heartbeat`, etc.). |
| `request_id` | String | ✅ Yes (except heartbeat) | A unique identifier for tracking responses to commands. |
| `timestamp` | String | ✅ Yes  | ISO 8601 UTC timestamp of when the message was created. |
| `payload`   | Object | ✅ Yes  | Message-specific data based on the `type`. |

---

## Message Types and Payloads

### 1. Command (Sent by Control Plane)
Used to send instructions to an agent.

#### JSON Format:
```json
{
  "type": "command",
  "request_id": "123456",
  "timestamp": "2025-02-24T12:34:56Z",
  "payload": {
    "command": "restart",
    "parameters": {
      "delay_seconds": 10
    }
  }
}
```

#### Payload Fields:
| Field       | Type   | Required | Description |
|------------|--------|----------|-------------|
| `command`  | String | ✅ Yes  | The command to be executed (e.g., `restart`, `update`, `fetch_logs`). |
| `parameters` | Object | ❌ No | Additional parameters required by the command. |

---

### 2. Status Update (Sent by Agent)
Used to send periodic updates from the agent to the control plane.

#### JSON Format:
```json
{
  "type": "status_update",
  "timestamp": "2025-02-24T12:35:10Z",
  "payload": {
    "cpu_usage": "30%",
    "memory_usage": "1.5GB"
  }
}
```

#### Payload Fields:
| Field         | Type   | Required | Description |
|--------------|--------|----------|-------------|
| `cpu_usage`   | String | ✅ Yes  | CPU usage percentage. |
| `memory_usage` | String | ✅ Yes  | Memory usage in GB or MB. |

---

### 3. Heartbeat (Sent by Agent)
Used to indicate that an agent is alive and connected.

#### JSON Format:
```json
{
  "type": "heartbeat",
  "timestamp": "2025-02-24T12:36:00Z",
  "payload": {}
}
```

#### Payload Fields:
- **Empty payload `{}`** since a heartbeat message does not require additional data.

---

### 4. Response (Sent by Agent)
Acknowledges a command received from the control plane.

#### JSON Format:
```json
{
  "type": "response",
  "request_id": "123456",
  "timestamp": "2025-02-24T12:35:00Z",
  "payload": {
    "status": "success"
  }
}
```

#### Payload Fields:
| Field     | Type   | Required | Description |
|----------|--------|----------|-------------|
| `status`  | String | ✅ Yes  | Status of the command execution (`success`, `failed`). |
| `message` | String | ❌ No | Optional details about the response. |

---

### 5. Error (Sent by Either Party)
Used to notify the other party of an error in processing a request.

#### JSON Format:
```json
{
  "type": "error",
  "request_id": "123456",
  "timestamp": "2025-02-24T12:35:10Z",
  "payload": {
    "code": "INVALID_COMMAND",
    "message": "The command 'shutdown' is not recognized."
  }
}
```

#### Payload Fields:
| Field    | Type   | Required | Description |
|---------|--------|----------|-------------|
| `code`   | String | ✅ Yes  | Error code (e.g., `INVALID_COMMAND`, `TIMEOUT`). |
| `message` | String | ✅ Yes  | Description of the error. |

---

## Communication Flow
### 1. Sending a Command
1. **Control Plane** sends a `command` message to the agent.
2. **Agent** receives and processes the command.
3. **Agent** responds with a `response` message containing the result.

### 2. Sending Status Updates
1. **Agent** periodically sends a `status_update` to the control plane.
2. **Control Plane** logs or processes the data as needed.

### 3. Heartbeat Mechanism
1. **Agent** sends a `heartbeat` message every `X` seconds.
2. If the **Control Plane** does not receive heartbeats within a timeout period, it assumes the agent is disconnected.

### 4. Handling Errors
1. If an agent receives an invalid command, it responds with an `error` message.
2. If the control plane sends a malformed request, the agent should reply with an `error` message.

---

## Best Practices
✅ **Use a Unique `request_id`**: Always include a request ID in messages requiring a response.
✅ **Maintain Connection Resilience**: Agents should implement auto-reconnection logic.
✅ **Secure WebSocket Connection**: Use **TLS (wss://)** and authentication tokens to prevent unauthorized access.
✅ **Limit Payload Size**: Avoid large payloads; use object storage (e.g., S3) for large data transfers.
✅ **Implement Retry Mechanisms**: Retries should be implemented in case of network failures.

---

## Conclusion
This document defines a structured and scalable communication protocol between the **Control Plane** and **Agents** over **WebSockets using JSON**. By following these guidelines, we ensure efficient, reliable, and secure communication between distributed agents and the control plane.

