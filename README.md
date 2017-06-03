# EasyNetIITM

The project is intended to provide a cross platform application to access Internet inside IIT Madras effortlessly.  
Product highlights:  

1. Automated detection of IITM network.  
(Application finds of if the system is connected to IITM network or not)
2. Completly automated Sign in to Netaccess portal.
3. Encrypted storage of LDAP password.

### Environment

The project is developed as a Qt Application to ensure the cross platform compatibility. While UI related code are written in C++, the core parts including loggin into Netaccess portal is done using Python, which is triggered from C++.
