the client won't have an executable.
instead it will have an api that follows form of the template proto file. This folder creates that api

(1) connect
(2) api commands
(3) state (api commands can only be sent in a certain running state)
(4) maybe make each api command blokcing - depends on timing

The api will build ontop of the ipc_client_controller
main will invoke the api...and then pass a thread to start the api.
