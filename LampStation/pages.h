#pragma once
#ifndef PAGES_H
#define PAGES_H

const char LOGIN_page[] PROGMEM = R"=====(
<html>
    <head>
    <title>LampStation</title>
    </head>
<body>
    
    <!-- Block style -->
    <style>
        :root {
            --main-width: 350px;
        }
        body {
            margin: 0;
            padding: 0;
            color: #ffffff;
            background: #1a1d26;
            font-family: sans-serif;
        }
        .main-container {
            left: 0;
            right: 0;
            margin: 10px auto;
            width: var(--main-width);
        }
        .icontainer {
            display: table;
            background-color: #afafaf;
            outline: none;
            text-decoration: none;
            border-radius: 5px;
            padding: 5px;
            cursor: pointer;
            color: white;
            text-align: center;
            padding: 5px 10px;
            text-transform: uppercase;
        }
        .ibutton-yes {
            background-color: #67d06d;
            width: var(--main-width);
            padding: 10px 10px;
            font-weight: bold;
            margin-bottom: 20px;
        }
        .ibutton-yes:hover {
            background-color: #9100ff;
        }
        .ipanel {
            border-radius: 5px;
            background-color: #5f6576;
            min-width: var(--main-width);
            display: table;
            padding: 8px 10px 5px 10px;
        }
        .tittle-panel {
            font-weight: bold;
            font-size: 25px;
            margin-bottom: 20px;
            padding: 20px 10px;
            background: linear-gradient(to right, #9100ff, #f2c0ff);
        }
        .separator-panel {
            font-weight: bold;
            font-size: 20px;
            margin: 40px 0 20px 0;
        }
        .header-panel {
            border-radius: 5px 5px 0px 0px;
            margin-bottom: 0;
            text-transform: uppercase;
            font-weight: bold;
        }
        .body-panel {
            border-radius: 0px 0px 5px 5px;
            margin-bottom: 20px;
            background-color: #3a3f4e;
        }
        .text-field {
            border-radius: 5px;
            border: 0;
            margin: 5px 5px 5px 0px;
            padding: 5px;
            width: 100%;
        }
        .eye {
            position: relative;
            display: inline-block;
            margin-left: calc(var(--main-width) - 28px);
            margin-top: -28px;
            width: 15px;
            height: 15px;
            border: solid 2px #5f6576;
            border-radius: 75% 15%;
            transform: rotate(45deg);
        }
        .eye::before {
            content: '';
            display: block;
            position: absolute;
            width: 5px;
            height: 5px;
            border: solid 2px #5f6576;
            border-radius: 50%;
            left: 3px;
            top: 3px;
        }
        .eye:hover, .eye:hover i, .eye:hover::before {
            border-color: #1a1d26;
        }
        .eye i {
            content: '';
            display: none;
            position: absolute;
            width: 23px;
            height: 0;
            border: solid 1px #5f6576;
            left: -5px;
            top: 6.5px;
        }
    </style>
    <!-- Block style -->
    
    <!-- Block script -->
    <script>
        function GetXmlHttp() {
            var xmlhttp;
            try {
                xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                try {
                    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                } catch (E) {
                    xmlhttp = false;
                }
            }
            if (!xmlhttp && typeof XMLHttpRequest!='undefined') {
                xmlhttp = new XMLHttpRequest();
            }
            return xmlhttp;
        }
        function SendRequest(_req, _atr, _url, _async = true, _typeData = "urlencoded", _head = true) {
            _req.open('POST', _url, _async);
            if (_head) _req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            _req.send(_atr);
        }
        function SaveData() {
            var ssid = document.querySelector('#ssid').value;
            var password = document.querySelector('#password').value;
            
            if (ssid != "" && password != "") {
                document.querySelector('#restart').style.display = "inline-block";
                
                var req = GetXmlHttp();
                req.onreadystatechange = function() {  
                    if (req.readyState == 4) { 
                        if(req.status == 200) {
                            console.log('Response: ' + req.responseText);
                        } else { return; }
                    }
                }
                SendRequest(req, 'ssid=' + ssid + '&password=' + password, '/preData');
            }
        }
        function showPassword(obj) {
            var x = obj.previousSibling;
            var y = obj.firstElementChild;
            if (x.type === "password") {
                x.type = "text";
                y.style.display = "block";
            } else {
                x.type = "password";
                y.style.display = "none";
            }
        }
    </script>
    <!-- Block script -->
    
    <div class="main-container">
        
        <div class="ipanel tittle-panel">LampStation</div>
        
        <div class="ipanel separator-panel" id="restart" style="display: none; margin: 0 0 20px 0;">Restart device, please</div>
        
        <div class="ipanel header-panel">WiFi setup</div>
        <div class="ipanel body-panel">
            <div class="text-container"><input class="text-field" id="ssid" placeholder="SSID" type="text"></div>
            <div class="text-container"><input class="text-field" id="password" placeholder="Password" type="password"><i class="eye" onclick="showPassword(this)"><i></i></i></div>
        </div>
        
        <div class="icontainer ibutton-yes" onclick="SaveData()">Save</div>
    </div>
    
</body>
</html>
)=====";

const char MAIN_page[] PROGMEM = R"=====(
<html>
<head>
    <title>LampStation</title>
</head>
<body>
    <style>
        :root {
            --main-width: 350px;
            --color-limit: 130%;
            --color-start: 20;
            --color-alpha: 0.9;
            --color-red: var(--color-start);
            --color-green: var(--color-start);
            --color-blue: var(--color-start);
        }
        body {
            margin: 0;
            padding: 0;
            color: #ffffff;
            background: #1a1d26;
            font-family: sans-serif;
        }
        .main-container {
            left: 0;
            right: 0;
            margin: 20px auto;
            width: var(--main-width);
        }
        .icontainer {
            display: table;
            background-color: #afafaf;
            outline: none;
            text-decoration: none;
            border-radius: 5px;
            padding: 5px;
            cursor: pointer;
            color: white;
            text-align: center;
            padding: 5px 10px;
            text-transform: uppercase;
        }
        .link-container a {
            color: white;
            text-decoration: none;
        }
        .ibutton {
            background-color: #9d9d9d;
            width: calc(100% - 20px);
            padding: 10px 10px;
            margin: 5px 5px 5px 0px;
            font-weight: bold;
        }
        .ibutton:hover {
            background-color: #9100ff;
        }
        .danger {
            background-color: #d06d67;
        }
        .ibutton-yes {
            background-color: #67d06d;
            width: var(--main-width);
            padding: 10px 10px;
            font-weight: bold;
            margin-bottom: 20px;
        }
        .ibutton-yes:hover {
            background-color: #9100ff;
        }
        .ipanel {
            border-radius: 5px;
            background-color: #5f6576;
            min-width: var(--main-width);
            display: table;
            padding: 8px 10px 5px 10px;
        }
        .tittle-panel {
            padding: 0;
            min-width: calc(var(--main-width) + 20px);
            margin-bottom: 20px;
            background-color: white;
        }
        #title-panel-color {
            margin: 0;
            border-radius: 4px;
            font-weight: bold;
            font-size: 25px;
            padding: 20px 10px;
            text-shadow: 0px 0px 3px black;
            background: linear-gradient(to right, rgba(var(--color-red), var(--color-green), var(--color-blue), var(--color-alpha)), rgba(0, 0, 0, 0) var(--color-limit));
        }
        .separator-panel {
            font-weight: bold;
            font-size: 20px;
            margin: 40px 0 20px 0;
        }
        .header-panel {
            border-radius: 5px 5px 0px 0px;
            margin-bottom: 0;
            text-transform: uppercase;
            font-weight: bold;
        }
        .body-panel {
            border-radius: 0px 0px 5px 5px;
            margin-bottom: 20px;
            background-color: #3a3f4e;
        }
        .range-container, .checkbox-container {
            margin: 5px 5px 5px 0px;
        }
        .range-text, .checkbox-text {
            display: inline-block;
            vertical-align: middle;
            width: 100px;
        }
        .range-action, .checkbox-action, .range-value {
            vertical-align: middle;
        }
        .checkbox-action {
            -webkit-appearance: none;
            -moz-appearance: none;
            appearance: none;
            width: 55px;
            height: 29.5px;
            background: #d06d67;
            border: 2px solid #fff;
            border-radius: 100px;
            outline: none;
            cursor: pointer;
            transition: all 0.3s cubic-bezier(0.2, 0.85, 0.32, 1.2);
            box-shadow: inset 1px 1px 1px 1px rgba(0, 0, 0, 0.1);
        }
        .checkbox-action::after {
            content: '';
            display: inline-block;
            position: absolute;
            margin: 3px;
            width: 16px;
            height: 16px;
            background-color: #676774;
            border: 2px solid #fff;
            border-radius: 50%;
            transform: translateX(0);
            transition: all 0.3s cubic-bezier(0.2, 0.85, 0.32, 1.2);
            box-shadow: 1px 1px 1px 1px rgba(0, 0, 0, 0.1);
        }
        .checkbox-action:hover::after {
            background-color: #484851;
        }
        .checkbox-action:checked::after {
            transform: translateX(calc(100% + 5px));
        }
        .checkbox-action:checked {
            background-color: #67d06d;
        }
        .range-value {
            display: inline-block;
            vertical-align: middle;
            padding: 0 5px;
        }
        .text-field {
            border-radius: 5px;
            border: 0;
            margin: 5px 5px 5px 0px;
            padding: 5px;
            width: 100%;
        }
        .eye {
            position: relative;
            display: inline-block;
            margin-left: calc(var(--main-width) - 28px);
            margin-top: -28px;
            width: 15px;
            height: 15px;
            border: solid 2px #5f6576;
            border-radius: 75% 15%;
            transform: rotate(45deg);
        }
        .eye::before {
            content: '';
            display: block;
            position: absolute;
            width: 5px;
            height: 5px;
            border: solid 2px #5f6576;
            border-radius: 50%;
            left: 3px;
            top: 3px;
        }
        .eye:hover, .eye:hover i, .eye:hover::before {
            border-color: #1a1d26;
        }
        .eye i {
            content: '';
            display: none;
            position: absolute;
            width: 23px;
            height: 0;
            border: solid 1px #5f6576;
            left: -5px;
            top: 6.5px;
        }
    </style>
    <!-- Block style -->
    <!-- Block script -->
    <script>
        function GetXmlHttp() {
            var xmlhttp;
            try {
                xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                try {
                    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                } catch (E) {
                    xmlhttp = false;
                }
            }
            if (!xmlhttp && typeof XMLHttpRequest!='undefined') {
                xmlhttp = new XMLHttpRequest();
            }
            return xmlhttp;
        }
        function SendRequest(_req, _atr, _url, _async = true, _typeData = "urlencoded", _head = true) {
            if (_typeData == "urlencoded") {
                _req.open('POST', _url, _async);
                if (_head) _req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            } else if (_typeData == "json") {
                _req.open('POST', _url, _async);
                if (_head) _req.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
            }

            _req.send(_atr);
        }
        function SaveData() {
            var ssid = document.querySelector('#ssid').value;
            var password = document.querySelector('#password').value;
            var local_device_name = document.querySelector('#local-device-name').value;
            var remote_device_name = document.querySelector('#remote-device-name').value;
            var mqtt_service_host = document.querySelector('#mqtt-service-host').value;
            var mqtt_service_port = document.querySelector('#mqtt-service-port').value;
            var mqtt_service_user = document.querySelector('#mqtt-service-user').value;
            var mqtt_service_pass = document.querySelector('#mqtt-service-pass').value;
            var light = 0;
            if (document.querySelector('#light').checked) {
                light = 1;
            }
            var color_red = document.querySelector('#color-red').value;
            var color_green = document.querySelector('#color-green').value;
            var color_blue = document.querySelector('#color-blue').value;
            
            if (ssid != "") {
                document.querySelector('#restart').style.display = "inline-block";
            
                var req = GetXmlHttp();
                req.onreadystatechange = function() {
                    if (req.readyState == 4) {
                        if(req.status == 200) {
                            console.log('Response: ' + req.responseText);
                        } else { return; }
                    }
                }
                SendRequest(req, 'ssid=' + ssid + 
                                '&password=' + password +
                                '&local_device_name=' + local_device_name +
                                '&remote_device_name=' + remote_device_name +
                                '&mqtt_service_host=' + mqtt_service_host +
                                '&mqtt_service_port=' + mqtt_service_port +
                                '&mqtt_service_user=' + mqtt_service_user +
                                '&mqtt_service_pass=' + mqtt_service_pass +
                                '&light=' + light +
                                '&color_red=' + color_red +
                                '&color_green=' + color_green +
                                '&color_blue=' + color_blue,
                                '/saveData');
            }
        }
        function LoadData(first_load) {
            var req = GetXmlHttp();
            req.onreadystatechange = function() {  
                if (req.readyState == 4) { 
                    if (req.status == 200) {
                        var data = req.responseText;
                        if (data != 'none') {
                            var split_data = data.split(' ');
                            for (var i = 0; i < split_data.length; i++)
                            {
                                path_data = split_data[i].split(':');
                                // TODO: FIX ME PLEASE!
                                if (path_data[0] == 'light') {
                                    if (path_data[1] == '0') {
                                        document.querySelector('#light').checked = false;
                                    } else {
                                        document.querySelector('#light').checked = true;
                                    }
                                } else {
                                    document.querySelector('#' + path_data[0]).value = path_data[1];
                                }
                            }
                        }
                        console.log('Response: ' + req.responseText);
                        setColor();
                    } else { return; }
                }
            }
            SendRequest(req, '', '/loadData?firstFlag=' + first_load);
        }
        
        LoadData(true);
        
        setInterval(function() {
          LoadData(false);
        }, 8000);
        
        function SendSimpleRequest(requestValue) {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', requestValue, false);
            xhr.send();
        }

        function showPassword(obj) {
            var x = obj.previousSibling;
            var y = obj.firstElementChild;
            if (x.type === "password") {
                x.type = "text";
                y.style.display = "block";
            } else {
                x.type = "password";
                y.style.display = "none";
            }
        }
        function setColor(obj = null, color = null) {
            if (color != null) {
                var root = document.documentElement;
                var color_start = parseInt(getComputedStyle(root).getPropertyValue('--color-start'));
                var new_color = Math.min(parseInt(obj.value) * (255 - color_start) / 255 + color_start, 255)
                root.style.setProperty('--color-' + color, new_color);
            }
            var title = document.querySelector('#title-panel-color');
            title.style.background = "linear-gradient(to right, rgba(var(--color-red), var(--color-green), var(--color-blue), var(--color-alpha)), rgba(0, 0, 0, 0) var(--color-limit)) no-repeat";
        }
    </script>
    <!-- Block script -->
    
    <div class="main-container">
        
        <div class="ipanel tittle-panel"><div id="title-panel-color">LampStation</div></div>
        
        <div class="ipanel header-panel">State</div>
        <div class="ipanel body-panel">
            <div class="checkbox-container"><div class="checkbox-text">Light:</div><input class="checkbox-action" id="light" type="checkbox"></div>
            <!--<div class="range-container"><div class="range-text">Brightness:</div><input class="range-action" id="bright" type="range" value="0" min=0 max="255" oninput="this.nextElementSibling.innerHTML = this.value"><div class="range-value">0</div></div>-->
            <div class="range-container"><div class="range-text">Red:</div><input class="range-action" id="color-red" type="range" value="0" min=0 max="255" oninput="this.nextElementSibling.innerHTML = this.value" onchange="setColor(this, 'red');"><div class="range-value">0</div></div>
            <div class="range-container"><div class="range-text">Green:</div><input class="range-action" id="color-green" type="range" value="0" min=0 max="255" oninput="this.nextElementSibling.innerHTML = this.value" onchange="setColor(this, 'green');"><div class="range-value">0</div></div>
            <div class="range-container"><div class="range-text">Blue:</div><input class="range-action" id="color-blue" type="range" value="0" min=0 max="255" oninput="this.nextElementSibling.innerHTML = this.value" onchange="setColor(this, 'blue');"><div class="range-value">0</div></div>
            <div class="range-container"><div class="range-text">Pair online:</div><input class="range-action" disabled id="pair-status" type="text"></div>
            <div class="range-container"><div class="range-text">MQTT ok:</div><input class="range-action" disabled id="mqtt-status" type="text"></div>
        </div>
        
        <div class="ipanel header-panel">Functions</div>
        <div class="ipanel body-panel">
            <div class="icontainer ibutton" onclick="SendSimpleRequest('/restart')">Restart</div>
            <div class="icontainer ibutton danger" onclick="if (confirm('Are you sure you want to reset to factory defaults?')) { SendSimpleRequest('/reset'); }">Reset</div>
        </div>
        
        <div class="ipanel separator-panel">Settings</div>
        
        <div class="ipanel separator-panel" id="restart" style="display: none; margin: 0 0 20px 0;">Restart device, if you change wifi data</div>
        
        <div class="ipanel header-panel">WiFi</div>
        <div class="ipanel body-panel">
            <div class="text-container"><input class="text-field" id="ssid" placeholder="SSID" type="text"></div>
            <div class="text-container"><input class="text-field" id="password" placeholder="Password (empty = no change)" type="password"><i class="eye" onclick="showPassword(this)"><i></i></i></div>
        </div>
        
        <div class="ipanel header-panel">MQTT</div>
        <div class="ipanel body-panel">
            <div class="text-container"><input class="text-field" id="local-device-name" placeholder="Name of this device" type="text"></div>
            <div class="text-container"><input class="text-field" id="remote-device-name" placeholder="Name of remote device" type="text"></div>
            <div class="text-container"><input class="text-field" id="mqtt-service-host" placeholder="MQTT server host" type="text"></div>
            <div class="text-container"><input class="text-field" id="mqtt-service-port" placeholder="MQTT server port" type="text"></div>
            <div class="text-container"><input class="text-field" id="mqtt-service-user" placeholder="MQTT username" type="text"></div>
            <div class="text-container"><input class="text-field" id="mqtt-service-pass" placeholder="MQTT password (empty = no change)" type="password"><i class="eye" onclick="showPassword(this)"><i></i></i></div>
        </div>
        
        <div class="icontainer ibutton-yes" onclick="SaveData()">Save</div>
    </div>
    
</body>
</html>
)=====";

#endif // PAGES_H
