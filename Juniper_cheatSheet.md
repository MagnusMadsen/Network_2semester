# Juniper SRX cheatsheet

#Help

help 
<command> ?

#Show

show configuration 
show configuration | display set 
show configuration | display set | match [customer|ip|etc]

#Interface/customer/VLAN

set interfaces [interface] unit [vlan] description "[Interface or customer name]" 
set interfaces [interface] unit [vlan] vlan-id [vlan-id] 
set interfaces [interface] unit [vlan] family inet address [Range with gateway] 
set security zones security-zone hosting interfaces [interface.vlan]

#Address

set security zones security-zone untrust address-book address [address-name] [ip/range]

#Address set

set security zones security-zone untrust address-book address-set [adress-set-name] address [address-name]

#NAT

set security nat static rule-set [rule-set-name] rule [rule-name] match destination-address [external-ip] 
set security nat static rule-set [rule-set-name] rule [rule-name] then static-nat prefix [internal-ip]

#Application

set applications application [application-name] protocol tcp 
set applications application [application-name] destination-port [port]

#Policy

set security policies from-zone untrust to-zone hosting policy [policy-name] match source-address [any|address-name] 
set security policies from-zone untrust to-zone hosting policy [policy-name] destination-address [destination-address-name] 
set security policies from-zone untrust to-zone hosting policy [policy-name] match application [application-name] 
set security policies from-zone untrust to-zone hosting policy [policy-name] then permit

#default-deny for new policies

edit security policies from-zone untrust to-zone hosting 
insert policy [policy-name] before policy default-deny

#Commit stuff

top # Go to top of configuration 
show | compare # Show new configuration compared to old 
commit check # Check if everything is ok / emulate commit 
commit confirmed 5 # Commit but roll back after 5 min to test if ok 
commit # Commit everything

#Rollback

rollback # If show | compare is not satisfying 
rollback 1 # Undo commit