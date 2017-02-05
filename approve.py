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
	while(1):
		with session() as c:
			try:
				c.post('https://netaccess.iitm.ac.in/account/login',
					data=login)
				response = c.post(
					'https://netaccess.iitm.ac.in/account/approve',
					data=approv)
				print response
				print "Netaccess Approved!"
				break
			except Exception:
				print "Error Approving NetAccess!\nCheck your connection"
			for i in range(5):
				print "Retrying in " +str(5-i) +"s..."
				sleep(1)
			print "Retrying..."
	print "Exiting..."
