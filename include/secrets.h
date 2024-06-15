/**
 * ESP32 secrets file
 * 
 * Contains information required to connect to WiFi and in-turn, AWS IoT
 * 
 * Authors: Vipul Deshpande, Jaime Burbano
 */


/*
  Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <pgmspace.h>

#define SECRET
#define THINGNAME "HelloWorld_Subscribe"

const char WIFI_SSID[] = "POCO F1";
const char WIFI_PASSWORD[] = "1234567890";
const char AWS_IOT_ENDPOINT[] = "a3p1687h4vahc6-ats.iot.eu-central-1.amazonaws.com";

/* Amazon Root CA 1 */
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

/* Device Certificate */
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUSjeoPR+wlYLrvsLbsimT1L9dIbswDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDExMDE1MTI1
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL/nmhzIPv5WLnu66Y0z
druG4kOZ/DcyKrzU+RgTb67qp99ZL9U61BaiU9u9S6fgN8JwlkoiCqA96Pd1HsP6
YMpZH4vkTPgO9IUhkP2JvLEDxg7SWteeunOpgvL0atwMGpYqFjyDFIZb4UWabW1J
bNQ3Y62Q8Lskt65oSrxsGBJw24vEU7bShVhgacsk1+kXLlIy/J+M5mwuNBQJ2Jv7
692dO0VRUJnUVYEYnPHa1B2kP1rnUZmL/iDvpZr5LRw6ZC1Oqj/e/J5n+wxEiBKb
2z9Zp35cwksb8oBXDNPczprpEpxlGbojwhGhTKxlnWLkWTt1OPYyqLRrb9sGtZ9L
PssCAwEAAaNgMF4wHwYDVR0jBBgwFoAUd/2hVQWs5sZTA0tcsVcqVYc8mYQwHQYD
VR0OBBYEFG6vuSLnbqH/LwyZQ6eDYbjRFhQHMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAbudmepItVQGT5azaadI6JS7SO
efc7SKYv0e7fiTnkDYHJCnJNadQUb7N54XvJw64oig7dHMzRE5rpQTuh/FRJ4e0y
9G+OsM4CDCgS3/GhyF+OF5H96RVdwRU7ob4/PMwWlmIDxH1qg4n3XiGOaasVA0+r
Nwv+DAzec4GXhqffC/cYFkeF5vpofChO6zEZtSKkydBESvLMh7FAar+eHcRzHI8j
Ftkm7wQufaV5vRJeRGVhfX5K+2W+4Zy7fkau6iD/sDOL+qjwko2mvJBqrQS2oqti
DthTQrGThLgP/N9wQbggQLmHuuEBXJXDa6vrKr1Y54IrRif+9Uu6uGGfngkW
-----END CERTIFICATE-----
)KEY";

/* Device Private Key */
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAv+eaHMg+/lYue7rpjTN2u4biQ5n8NzIqvNT5GBNvruqn31kv
1TrUFqJT271Lp+A3wnCWSiIKoD3o93Uew/pgylkfi+RM+A70hSGQ/Ym8sQPGDtJa
1566c6mC8vRq3AwalioWPIMUhlvhRZptbUls1DdjrZDwuyS3rmhKvGwYEnDbi8RT
ttKFWGBpyyTX6RcuUjL8n4zmbC40FAnYm/vr3Z07RVFQmdRVgRic8drUHaQ/WudR
mYv+IO+lmvktHDpkLU6qP978nmf7DESIEpvbP1mnflzCSxvygFcM09zOmukSnGUZ
uiPCEaFMrGWdYuRZO3U49jKotGtv2wa1n0s+ywIDAQABAoIBAA/A74HVXnZ6lK5L
lcilpOWYGRL7nRza3W9K/HfhgJWXZdiL9cVHYwnIoaG0VHWfjnRD0dKcIMsuyeUm
lDP6Zd+2mURepYLnl2MmckSd/gN6D9Q/qH1y5lOAYuOW9P7Db5tMMS8eg5zUBhY0
qy8BjBGPynsBHwH97aY/oYL+TKuWu28Sf7I2KcMR+7rUcZMOrOEPDhV1iDC2Vi5r
etIIDcalduaI3A2HGXu/r1WEqf5OxBIZO9Be3av4aGQaxhfnnGSIPbxDekjXc0p9
MxXVzBf4Cx2+DhgHgwwsqhL3MuaBEmcxXN3Ds3TVJ023Vbacqcm02LNDhYquYpVO
pamlUcECgYEA/w6kZNnCxpmMJvnhau01hJQTS9wPI9CjgwhysepI5V5D7Q3WKZch
WwiLxR/5iJPLPszLqigDtwP5E+pAGVEvpUrM/z/il0jW16HPCUll37aCcHc1HPnc
xE5WsffZ9YlrtWBaCuMLkROo/Eze5JJS/Vi2PWo7teUooYO7wQMTJrkCgYEAwJ0z
Bm5jflqI8hOukJmoL17E8RJ/lcWtASPfzMjIiteCiNb+K3cIrQ89U6ufdmmlHjTH
b2imQOMxXYOnRYiIu6RtYnVdWGBVXfJVomyqkNz2SHQpLR34a397ND02JkNb0nfR
w7MYIh7ebAaDtCdwCAaYCjJ/MJBDgddUVLcaz6MCgYEAmuvK4NMAIt9bKMV4rRj9
+9RxUA+PRqLQ3qM//18d/eve+FsCLWr1wLSVKRv91n5m4nNEdcsuTnjkTrtnSblt
Zknj8FpeiKOek4VeGvbxIQxbeHJ/2WTPOpGWySyRwDlDKf0nVBuKiAlYCD+s10sl
i2rZ7r3bHOXfYxN/9IGonUkCgYEAsaSJ+cV3l4IySWljl1NP7RhvdJMF/oEI1UNb
1gfcBUlLx57ZXgbzhoDGo9NmR5SZx6kPwq12n+OplMCmVhfdW4oDpEnwJGD8ep/U
4O9txBs2PY58p3K7uZEidQR7W4DGP+9oFCCqAlYL9v9vGolA5vYF5Wm7KnPy/t40
lckmPhcCgYEA/FxJWU4YA8XLR3wCScoxbFHBY8Ixt1IO57UCMLpsHLweMrKjJsA2
2Ta7g52ckqA7HfKHcvdVLxBa7TOhzwz89tj6ihuHW+eRU4ecUhufCKvIfIcV3dls
/JJ0yUmDCxiCH4VGag+f1+5Bd60/EFXz7d1pwUtyc9uRALob74z9dts=
-----END RSA PRIVATE KEY-----
)KEY";