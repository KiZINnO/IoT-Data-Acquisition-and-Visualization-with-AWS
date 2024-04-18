#include <pgmspace.h>
#define SECRET
#define THINGNAME "mqtt"

const char AWS_IOT_ENDPOINT[] = "a1x9fj1vj5qdlg-ats.iot.us-east-1.amazonaws.com";

// Amazon Root CA 1
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

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUXhBwvtc0Mm6LKZ0WMKYG+zeizCswDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDMxNzA4MTky
NFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMr/yFVTCFFuZfF4Sy/a
/27CSS3LI8PzwUqxPoR/c4JBxqu55DnhqSkpdXiZW5SPTOMrKenVvtk/0uixem0E
RDu9ALWLp1gs+0GG0IT86JJ2cXf4//cykuKlm/NBMzV470RJ2jBBfPg8sXozW/Nu
cHBCoblMTeR9S9sLyt17LKj0RgCX0iQW3CrQBnGUCPpse2jEcNUF58bJWGP+Isdj
mmGp/Z1kZB251mVX9OV2i660VPDZfjjxcqi7yxcbxyRnLTmeWm2MhTMewuafRcpd
BMFK1nZx+f65a9Zf7ZlOaIQI2+QUvM96umt7TNUXhMhOcpIGXhcrUB8N5jd9HUGd
qgECAwEAAaNgMF4wHwYDVR0jBBgwFoAUO6a0SKMzvHv+W96P90RGWklpYAIwHQYD
VR0OBBYEFEGj/R/1rljT6gXZ49lDM0vpw/AkMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQC63l+glGP9gx5NX7Eo5LYIfIAm
TX7fuRWJjrADewk2TQgVy2dsMQ1HdPj4hcOFId7p7JAO2p4SpuBH6atrbyOp321M
UQc++z3tsymKJqI8vpLk+DHqer++3L79X3GycOdFZhbwh0+jDS2J+95ioo3zXvfn
tOTTt1MwmU3bsLEQz0T7PDQYCNXgHfMvTeO9YkDbqheu1PmSM8jcfXYiRczU1kEn
dFuHhBdsqnlsCWwG6bCeZky2avnENFIg8nFzf9W4PfDjM439y7HcCvcHhqv6oHEq
BxDgyluqhZSJOEtzHjgqBzF1Pyaaoj32G4/gXSNTQDC/xPKNPc5Fnd/Dlcan
-----END CERTIFICATE-----

)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAyv/IVVMIUW5l8XhLL9r/bsJJLcsjw/PBSrE+hH9zgkHGq7nk
OeGpKSl1eJlblI9M4ysp6dW+2T/S6LF6bQREO70AtYunWCz7QYbQhPzoknZxd/j/
9zKS4qWb80EzNXjvREnaMEF8+DyxejNb825wcEKhuUxN5H1L2wvK3XssqPRGAJfS
JBbcKtAGcZQI+mx7aMRw1QXnxslYY/4ix2OaYan9nWRkHbnWZVf05XaLrrRU8Nl+
OPFyqLvLFxvHJGctOZ5abYyFMx7C5p9Fyl0EwUrWdnH5/rlr1l/tmU5ohAjb5BS8
z3q6a3tM1ReEyE5ykgZeFytQHw3mN30dQZ2qAQIDAQABAoIBAQCddpNbPDEzmUMS
b5FC6clBjQterjhsA2RoH9yywnpDC+qjwmo6S8T/3Nz2U18qeY3WmODGNbr4of1j
6mdgsPKMtCscp9uDFkE/rueIgPWWxrF1snw6r8woavXxVx312H0gp3jL/cCGfe3d
MIGe7ofhTI5OQdYZ6ucwXpFaA/W8h3ucQN4msdavN+ieaBOCLelmsxLHDW5DFBuu
qRFGX4PdmJsi0aQzP8jjSR++gQr2ws1Kjia5DhDL3JmnoVPtz/i7xoSEBR/Uf1lr
tzQhYCiMNqKB9hncq7fdLQPItZaYD9WdAXwP5c/rH+xQW4Rd/T34e8HVZbYxYYdD
S1eM2hyRAoGBAPpqP47UBndxuHkE0aJOdPg2UdDgHs+IwdHZAOtrQ1Oet43wZQD9
z9Sebz1AlGsAt/VHFV/FZs6XwhCgu3Gvpim/vffZTEyzhGQ1jvxmnyC8Ljiw3wcr
AdhjyzHcPxMcDs8fr2q2TzSjgZHttCjbK75up70NbAbukWOYTBN4b8mrAoGBAM+G
z9x2uAnU4GayrEYwhapKvPIhVmtpOYHQwuwRP/NNeC71Y2xdrFkP6wTBD0gFMnAS
seIGlT89Z4V257fwxrOHaqBdnT4miKyrs89b8eQJygP0i38XIOHHrn3eu4BIYUZ+
TU37beAO67FvZVmAZPmad7xoKSP4JbCVoWxI/+cDAoGATv+jy2hCHf5nRu5pP/3m
UsO4Ld/2eFxZYN1Ht/0fwUqJ96JGCvkHTrkouLcd21/fqOZi7NK2qygfFeXPHH9g
OT1/LaiEtJHRi1eGI0QwoUAciM/rnDRKIbzhxnoH//xTA66oRU78T8vhPWsy8cyq
0SnRiwen88vhW/0Yyu+svH8CgYBPUa63DCVRlKzkc9xGw5sDOKe5QCbAzSouxPUL
t5gizXRnNmF29OK/88aXPZcyptHdZjfZNTzsO/MKXyU39+5qhhKqEr3cGGxa2xHR
6smsqFUvZ9O9ksB9q421DGHMKV4MzI+Ng9E+N1W8ruAk8l8ly/WB7Kn01o7JTJez
RL+SswKBgQDATq+Xx2Z2DUbzhtdrp7E6YXIzZ5qVf0BsTIr0hiLHSh8qorwA4Mu9
ceWeYnKA4x6n7LTPzxRhItHq9nkljBw/2tn/NOKIfWSK+Z3Ac6vx6baGWnQyXi7z
+x4FNDuNjTerKF4LEa9rTpFjByvxVxm7arJfhGFWgJ+Q76aY7Ld/4w==
-----END RSA PRIVATE KEY-----

)KEY";