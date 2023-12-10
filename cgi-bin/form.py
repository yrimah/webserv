import cgi, cgitb 

form = cgi.FieldStorage() 

first_name = form.getvalue('first_name')
last_name  = form.getvalue('last_name')

print ("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n")

print ("<html>")
print ("<head>")
print ("<title>Hello - Second CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<h2>Hello %s %s</h2>" % (first_name, last_name))
print ("</body>")
print ("</html>")