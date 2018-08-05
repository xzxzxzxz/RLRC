// Auto-generated. Do not edit!

// (in-package path_follower.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class traj_plan {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.j = null;
      this.i = null;
      this.x = null;
      this.y = null;
      this.theta = null;
      this.v = null;
      this.rate_yaw = null;
    }
    else {
      if (initObj.hasOwnProperty('j')) {
        this.j = initObj.j
      }
      else {
        this.j = 0;
      }
      if (initObj.hasOwnProperty('i')) {
        this.i = initObj.i
      }
      else {
        this.i = 0;
      }
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = 0.0;
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = 0.0;
      }
      if (initObj.hasOwnProperty('theta')) {
        this.theta = initObj.theta
      }
      else {
        this.theta = 0.0;
      }
      if (initObj.hasOwnProperty('v')) {
        this.v = initObj.v
      }
      else {
        this.v = 0.0;
      }
      if (initObj.hasOwnProperty('rate_yaw')) {
        this.rate_yaw = initObj.rate_yaw
      }
      else {
        this.rate_yaw = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type traj_plan
    // Serialize message field [j]
    bufferOffset = _serializer.int32(obj.j, buffer, bufferOffset);
    // Serialize message field [i]
    bufferOffset = _serializer.int32(obj.i, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _serializer.float64(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float64(obj.y, buffer, bufferOffset);
    // Serialize message field [theta]
    bufferOffset = _serializer.float64(obj.theta, buffer, bufferOffset);
    // Serialize message field [v]
    bufferOffset = _serializer.float64(obj.v, buffer, bufferOffset);
    // Serialize message field [rate_yaw]
    bufferOffset = _serializer.float64(obj.rate_yaw, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type traj_plan
    let len;
    let data = new traj_plan(null);
    // Deserialize message field [j]
    data.j = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [i]
    data.i = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [theta]
    data.theta = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [v]
    data.v = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rate_yaw]
    data.rate_yaw = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 48;
  }

  static datatype() {
    // Returns string type for a message object
    return 'path_follower/traj_plan';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f8c2ada89420e3e8b85c22cafba5a2f5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 j
    int32 i
    float64 x
    float64 y
    float64 theta
    float64 v
    float64 rate_yaw
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new traj_plan(null);
    if (msg.j !== undefined) {
      resolved.j = msg.j;
    }
    else {
      resolved.j = 0
    }

    if (msg.i !== undefined) {
      resolved.i = msg.i;
    }
    else {
      resolved.i = 0
    }

    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = 0.0
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = 0.0
    }

    if (msg.theta !== undefined) {
      resolved.theta = msg.theta;
    }
    else {
      resolved.theta = 0.0
    }

    if (msg.v !== undefined) {
      resolved.v = msg.v;
    }
    else {
      resolved.v = 0.0
    }

    if (msg.rate_yaw !== undefined) {
      resolved.rate_yaw = msg.rate_yaw;
    }
    else {
      resolved.rate_yaw = 0.0
    }

    return resolved;
    }
};

module.exports = traj_plan;
