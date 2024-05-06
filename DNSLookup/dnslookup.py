import socket 
def dns_lookup():
    print("DNS Lookup")
    link="a"
    while link !="end":
        link=input("Enter the website name: ")
        if link != "end":
            host = socket.gethostbyname(link)
            print("IP address of", link, "is", host, "\n")
    print("Closed.")
  
if __name__ == '__main__':
  dns_lookup()
