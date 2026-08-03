A C implementation of a multithreaded HTTP/1.1/2.0 server. 

## Goals:

### Phase 1 
  * Implement a basic HTTP/1 server
  * Have server use threads to accept clients
  * Serve static file on request.
### Phase 2
  * Implement HTTP/2 protocol
### Phase 3
  * Implement HTTPS protocol
### Phase 4
  * A final, additional goal of implementing an html server template system. 

## AI Disclosure:

Generative AI is not to be used in this project, as that would invalidate the entire point of the learning exercise. However the use of non-generative AI may be permitted in the cases of:
* Helping to find relevant module info from the POSIX C Man Pages.
* Helping in cases where an obtuse syntax error exists in the code and only then should the console output or singular lines of code be sent.
* Questions relating to the general conventions that should be used when writing of C.

## Resources
* POSIX and Linux Man Pages (and the ever so helpful man7.org)
* [RFC 9112 (HTTP/1.1)](https://datatracker.ietf.org/doc/html/rfc9112)
* [RFC 9113 (HTTP/2)](https://datatracker.ietf.org/doc/rfc9113/)
