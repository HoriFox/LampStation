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
        body {
            margin: 0;
            padding: 0;
            color: #ffffff;
            background: #1a1d26;
            font-family: sans-serif;
        }
        .main-container {
            margin: 10px;
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
            width: 300px;
            padding: 10px 10px;
            font-weight: bold;
            margin-bottom: 20px;
        }
        .ipanel {
            border-radius: 5px;
            background-color: #5f6576;
            min-width: 300px;
            display: table;
            padding: 5px 10px;
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
                SendRequest(req, 'ssid=' + ssid + 
                                '&password=' + password, '/preData');
            }
        }
    </script>
    <!-- Block script -->
    
    <div class="main-container">
        
        <div class="ipanel tittle-panel">LampStation</div>
        
        <div class="ipanel separator-panel" id="restart" style="display: none; margin: 0 0 20px 0;">Restart device, please</div>
        
        <div class="ipanel header-panel">WiFi</div>
        <div class="ipanel body-panel">
            <div class="text-container"><input class="text-field" id="ssid" placeholder="SSID..." type="text"></div>
            <div class="text-container"><input class="text-field" id="password" placeholder="Password..." type="password"></div>
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
    
    <!-- Block style -->
    <style>
        body {
            margin: 0;
            padding: 0;
            color: #ffffff;
            background: #1a1d26;
            font-family: sans-serif;
        }
        .main-container {
            margin: 10px;
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
        .ibutton-yes {
            background-color: #67d06d;
            width: 300px;
            padding: 10px 10px;
            font-weight: bold;
            margin-bottom: 20px;
        }
        .ipanel {
            border-radius: 5px;
            background-color: #5f6576;
            min-width: 300px;
            display: table;
            padding: 5px 10px;
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
            var ip_mqtt_service = document.querySelector('#ip-mqtt-service').value;
            var port_mqtt_service = document.querySelector('#port-mqtt-service').value;
            
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
                SendRequest(req, 'ssid=' + ssid + 
                                '&password=' + password +
                                '&local_device_name=' + local_device_name +
                                '&remote_device_name=' + remote_device_name +
                                '&ip_mqtt_service=' + ip_mqtt_service +
                                '&port_mqtt_service=' + port_mqtt_service, '/saveData');
            }
        }
        function LoadData(first_load) {
            var req = GetXmlHttp();
            req.onreadystatechange = function() {  
                if (req.readyState == 4) { 
                    if(req.status == 200) {
                        var data = req.responseText;
                        if (data != 'none') {
                            var split_data = data.split(' ');
                            for (var i = 0; i < split_data.length; i++)
                            {
                                path_data = split_data[i].split(':');
                                document.querySelector('#' + path_data[0]).value = path_data[1];
                            }
                        }
                        console.log('Response: ' + req.responseText);
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
    </script>
    <!-- Block script -->
    
    <div class="main-container">
        
        <div class="ipanel tittle-panel">LampStation</div>
        
        <div class="ipanel header-panel">condition</div>
        <div class="ipanel body-panel">
            <div class="checkbox-container"><div class="checkbox-text">Power</div><input class="checkbox-action" id="power" type="checkbox"></div>
            <div class="range-container"><div class="range-text">Brightness</div><input class="range-action" id="bright" type="range" value="0" min=0 max="255" oninput="this.nextElementSibling.innerHTML = this.value"><div class="range-value">0</div></div>
            <div class="range-container"><div class="range-text">Color</div><input class="range-action" id="color" type="range" value="0" min=0 max="255" oninput="this.nextElementSibling.innerHTML = this.value"><div class="range-value">0</div></div>
        </div>
        
        <div class="ipanel header-panel">Functions</div>
        <div class="ipanel body-panel">
            <div class="icontainer ibutton" onclick="SendSimpleRequest('/restart')">Restart</div>
        </div>
        
        <div class="ipanel separator-panel">Setting</div>
        
        <div class="ipanel separator-panel" id="restart" style="display: none; margin: 0 0 20px 0;">Restart device, if you change wifi data</div>
        
        <div class="ipanel header-panel">WiFi</div>
        <div class="ipanel body-panel">
            <div class="text-container"><input class="text-field" id="ssid" placeholder="SSID..." type="text"></div>
            <div class="text-container"><input class="text-field" id="password" placeholder="Password..." type="password"></div>
        </div>
        
        <div class="ipanel header-panel">MQTT</div>
        <div class="ipanel body-panel">
            <div class="text-container"><input class="text-field" id="local-device-name" placeholder="Name current device..." type="text"></div>
            <div class="text-container"><input class="text-field" id="remote-device-name" placeholder="Name remote device..." type="text"></div>
            <div class="text-container"><input class="text-field" id="ip-mqtt-service" placeholder="IP MQTT server..." type="text"></div>
            <div class="text-container"><input class="text-field" id="port-mqtt-service" placeholder="Port MQTT server..." type="text"></div>
        </div>
        
        <div class="icontainer ibutton-yes" onclick="SaveData()">Save</div>
    </div>
    
</body>
</html>
)=====";

#endif // PAGES_H
