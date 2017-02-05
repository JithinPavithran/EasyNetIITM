from requests import session
import httplib
import urllib2, urllib
import sys
from time import sleep


def validate(roll_no, pass_w):
	login = {
		'submit': '',
		'userLogin': roll_no,
		'userPassword': pass_w
	}
	res = session().post("https://netaccess.iitm.ac.in/account/login",
				data=login)
	
	if res.status_code == 200:
		if res.url == 'https://netaccess.iitm.ac.in/account/index':
			print "Credentials Validated"
			# return 1
		else:
			print "Invalid Credentials"
			# return 0
	else:
		print "Validation falied - Possibly connection Error"
		# return -1
