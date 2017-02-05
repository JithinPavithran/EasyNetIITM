from requests import session
import httplib
import urllib2, urllib
import sys
from time import sleep


def approve(duration, username, password):
    """
    duration: 1: 1hour, 2: 1day
    """
    approv = {
        'duration': duration,
        'approveBtn': '',
    }
    login = {
        'submit': '',
        'userLogin': username,
        'userPassword': password
    }
    c = session()
    try:
        c.post('https://netaccess.iitm.ac.in/account/login', \
            data=login)
        response = c.post('https://netaccess.iitm.ac.in/account/approve', \
            data=approv)
        print username
        print password
        print response
        print response.url
        print response.status_code

        if response.status_code == 200 \
            and response.url == 'https://netaccess.iitm.ac.in/account/index':
            # TODO: replace this simple test with actual ip test
            print "Netaccess Approved!"
            return 0
        else:
            print "Approval failed!"
            return 1

    except Exception:
        print "Error Approving NetAccess!\nCheck your connection"
        return 1
