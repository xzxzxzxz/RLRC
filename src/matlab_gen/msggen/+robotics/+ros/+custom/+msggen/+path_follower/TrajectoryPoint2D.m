classdef TrajectoryPoint2D < robotics.ros.Message
    %TrajectoryPoint2D MATLAB implementation of path_follower/TrajectoryPoint2D
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2018 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'path_follower/TrajectoryPoint2D' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '63ab900fed4c2c35d54c1d98c787e72b' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Dependent)
        T
        X
        Y
        Theta
        Kappa
        KappaDot
        V
        A
        Jerk
        DeltaTheta
        D
        ALat
    end
    
    properties (Constant, Hidden)
        PropertyList = {'A', 'ALat', 'D', 'DeltaTheta', 'Jerk', 'Kappa', 'KappaDot', 'T', 'Theta', 'V', 'X', 'Y'} % List of non-constant message properties
        ROSPropertyList = {'a', 'a_lat', 'd', 'delta_theta', 'jerk', 'kappa', 'kappa_dot', 't', 'theta', 'v', 'x', 'y'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = TrajectoryPoint2D(msg)
            %TrajectoryPoint2D Construct the message object TrajectoryPoint2D
            import com.mathworks.toolbox.robotics.ros.message.MessageInfo;
            
            % Support default constructor
            if nargin == 0
                obj.JavaMessage = obj.createNewJavaMessage;
                return;
            end
            
            % Construct appropriate empty array
            if isempty(msg)
                obj = obj.empty(0,1);
                return;
            end
            
            % Make scalar construction fast
            if isscalar(msg)
                % Check for correct input class
                if ~MessageInfo.compareTypes(msg(1), obj.MessageType)
                    error(message('robotics:ros:message:NoTypeMatch', obj.MessageType, ...
                        char(MessageInfo.getType(msg(1))) ));
                end
                obj.JavaMessage = msg(1);
                return;
            end
            
            % Check that this is a vector of scalar messages. Since this
            % is an object array, use arrayfun to verify.
            if ~all(arrayfun(@isscalar, msg))
                error(message('robotics:ros:message:MessageArraySizeError'));
            end
            
            % Check that all messages in the array have the correct type
            if ~all(arrayfun(@(x) MessageInfo.compareTypes(x, obj.MessageType), msg))
                error(message('robotics:ros:message:NoTypeMatchArray', obj.MessageType));
            end
            
            % Construct array of objects if necessary
            objType = class(obj);
            for i = 1:length(msg)
                obj(i,1) = feval(objType, msg(i)); %#ok<AGROW>
            end
        end
        
        function t = get.T(obj)
            %get.T Get the value for property T
            t = double(obj.JavaMessage.getT);
        end
        
        function set.T(obj, t)
            %set.T Set the value for property T
            validateattributes(t, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'T');
            
            obj.JavaMessage.setT(t);
        end
        
        function x = get.X(obj)
            %get.X Get the value for property X
            x = double(obj.JavaMessage.getX);
        end
        
        function set.X(obj, x)
            %set.X Set the value for property X
            validateattributes(x, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'X');
            
            obj.JavaMessage.setX(x);
        end
        
        function y = get.Y(obj)
            %get.Y Get the value for property Y
            y = double(obj.JavaMessage.getY);
        end
        
        function set.Y(obj, y)
            %set.Y Set the value for property Y
            validateattributes(y, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'Y');
            
            obj.JavaMessage.setY(y);
        end
        
        function theta = get.Theta(obj)
            %get.Theta Get the value for property Theta
            theta = double(obj.JavaMessage.getTheta);
        end
        
        function set.Theta(obj, theta)
            %set.Theta Set the value for property Theta
            validateattributes(theta, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'Theta');
            
            obj.JavaMessage.setTheta(theta);
        end
        
        function kappa = get.Kappa(obj)
            %get.Kappa Get the value for property Kappa
            kappa = double(obj.JavaMessage.getKappa);
        end
        
        function set.Kappa(obj, kappa)
            %set.Kappa Set the value for property Kappa
            validateattributes(kappa, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'Kappa');
            
            obj.JavaMessage.setKappa(kappa);
        end
        
        function kappadot = get.KappaDot(obj)
            %get.KappaDot Get the value for property KappaDot
            kappadot = double(obj.JavaMessage.getKappaDot);
        end
        
        function set.KappaDot(obj, kappadot)
            %set.KappaDot Set the value for property KappaDot
            validateattributes(kappadot, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'KappaDot');
            
            obj.JavaMessage.setKappaDot(kappadot);
        end
        
        function v = get.V(obj)
            %get.V Get the value for property V
            v = double(obj.JavaMessage.getV);
        end
        
        function set.V(obj, v)
            %set.V Set the value for property V
            validateattributes(v, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'V');
            
            obj.JavaMessage.setV(v);
        end
        
        function a = get.A(obj)
            %get.A Get the value for property A
            a = double(obj.JavaMessage.getA);
        end
        
        function set.A(obj, a)
            %set.A Set the value for property A
            validateattributes(a, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'A');
            
            obj.JavaMessage.setA(a);
        end
        
        function jerk = get.Jerk(obj)
            %get.Jerk Get the value for property Jerk
            jerk = double(obj.JavaMessage.getJerk);
        end
        
        function set.Jerk(obj, jerk)
            %set.Jerk Set the value for property Jerk
            validateattributes(jerk, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'Jerk');
            
            obj.JavaMessage.setJerk(jerk);
        end
        
        function deltatheta = get.DeltaTheta(obj)
            %get.DeltaTheta Get the value for property DeltaTheta
            deltatheta = double(obj.JavaMessage.getDeltaTheta);
        end
        
        function set.DeltaTheta(obj, deltatheta)
            %set.DeltaTheta Set the value for property DeltaTheta
            validateattributes(deltatheta, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'DeltaTheta');
            
            obj.JavaMessage.setDeltaTheta(deltatheta);
        end
        
        function d = get.D(obj)
            %get.D Get the value for property D
            d = double(obj.JavaMessage.getD);
        end
        
        function set.D(obj, d)
            %set.D Set the value for property D
            validateattributes(d, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'D');
            
            obj.JavaMessage.setD(d);
        end
        
        function alat = get.ALat(obj)
            %get.ALat Get the value for property ALat
            alat = double(obj.JavaMessage.getALat);
        end
        
        function set.ALat(obj, alat)
            %set.ALat Set the value for property ALat
            validateattributes(alat, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryPoint2D', 'ALat');
            
            obj.JavaMessage.setALat(alat);
        end
    end
    
    methods (Access = protected)
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Iterate over all primitive properties
            cpObj.T = obj.T;
            cpObj.X = obj.X;
            cpObj.Y = obj.Y;
            cpObj.Theta = obj.Theta;
            cpObj.Kappa = obj.Kappa;
            cpObj.KappaDot = obj.KappaDot;
            cpObj.V = obj.V;
            cpObj.A = obj.A;
            cpObj.Jerk = obj.Jerk;
            cpObj.DeltaTheta = obj.DeltaTheta;
            cpObj.D = obj.D;
            cpObj.ALat = obj.ALat;
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.T = strObj.T;
            obj.X = strObj.X;
            obj.Y = strObj.Y;
            obj.Theta = strObj.Theta;
            obj.Kappa = strObj.Kappa;
            obj.KappaDot = strObj.KappaDot;
            obj.V = strObj.V;
            obj.A = strObj.A;
            obj.Jerk = strObj.Jerk;
            obj.DeltaTheta = strObj.DeltaTheta;
            obj.D = strObj.D;
            obj.ALat = strObj.ALat;
        end
    end
    
    methods (Access = ?robotics.ros.Message)
        function strObj = saveobj(obj)
            %saveobj Implements saving of message to MAT file
            
            % Return an empty element if object array is empty
            if isempty(obj)
                strObj = struct.empty;
                return
            end
            
            strObj.T = obj.T;
            strObj.X = obj.X;
            strObj.Y = obj.Y;
            strObj.Theta = obj.Theta;
            strObj.Kappa = obj.Kappa;
            strObj.KappaDot = obj.KappaDot;
            strObj.V = obj.V;
            strObj.A = obj.A;
            strObj.Jerk = obj.Jerk;
            strObj.DeltaTheta = obj.DeltaTheta;
            strObj.D = obj.D;
            strObj.ALat = obj.ALat;
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.path_follower.TrajectoryPoint2D.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.path_follower.TrajectoryPoint2D;
            obj.reload(strObj);
        end
    end
end
