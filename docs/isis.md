# ISIS

Intermediate System to Intermediate System (ISIS, also written IS-IS) 
is a routing protocol designed to move information efficiently within 
a network.

The ISIS protocol is defined in ISO/IEC 10589:2002 as an international 
standard within the Open Systems Interconnection (OSI) reference design. 
The Internet Engineering Task Force (IETF) republished ISIS in RFC 1142, 
but that RFC was later marked as historic by RFC 7142 because it republished 
a draft rather than a final version of the ISO standard, causing confusion.

ISIS has been called the de facto standard for large service provider 
network backbones.

The BNG Blaster is able to emulate multiple ISIS instances. An ISIS instance
is a virtual ISIS node with one or more network interfaces attached. Such a
node behaves like a "real router" including database synchronization and 
flooding. Every instance generates a `self` originated LSP describing the
node itself.

Following an example ISIS configuration with one instance 
attached to two network interfaces.

```json
{
    "interfaces": {
        "network": [
            {
                "interface": "eth1",
                "address": "10.0.1.2/24",
                "gateway": "10.0.1.1",
                "address-ipv6": "fc66:1337:7331:1::2/64",
                "gateway-ipv6": "fc66:1337:7331:1::1",
                "isis-instance-id": 1,
                "isis-level": 1,
                "isis-l1-metric": 100,
            },
            {
                "interface": "eth2",
                "address": "10.0.2.2/24",
                "gateway": "10.0.2.1",
                "address-ipv6": "fc66:1337:7331:2::2/64",
                "gateway-ipv6": "fc66:1337:7331:2::1",
                "isis-instance-id": 1
            }
        ]
    },
    "isis": [
        {
            "instance-id": 1,
            "system-id": "0100.1001.0010",
            "router-id": "10.10.10.10",
            "hostname": "R1",
            "area": [
                "49.0001/24",
                "49.0002/24"
            ],
            "hello-padding": true,
            "lsp-lifetime": 65535,
            "level1-auth-key": "secret",
            "level1-auth-type": "md5",
            "sr-base": 2000,
            "sr-range": 3600
        }
    ]
}
```

All supported ISIS [configuration](config) options and [commands](ctrl) are 
detailed explained corresponding sections of this documentation.

The support for multiple instances allows different use cases. One example might 
be to create two instances connected to the device or network under test. Now 
inject a LSP on one instance and check if learned over the tested network on 
the other instance. 

Every ISIS instance can be also connected to an emulated link state graph loaded 
by MRT files  as shown in the example below. 

![BBL ISIS](images/bbl_isis.png "ISIS")

```json
{
    "isis": [
        {
            "instance-id": 1,
            "system-id": "0100.1001.0011",
            "router-id": "10.10.10.11",
            "hostname": "B1",
            "external": {
                "mrt-file": "test.mrt",
                "connections": [
                    {
                        "system-id": "0000.0000.0001",
                        "l1-metric": 1000,
                        "l2-metric": 2000
                    }
                ]
            }
        },
        {
            "instance-id": 1,
            "system-id": "0100.1001.0011",
            "router-id": "10.10.10.12",
            "hostname": "B2"
        }
    ]
}
```

The node `N1` in this example also needs to advertise the 
reachability to the node `B1`.

## Adjacencies

The BNG Blaster supports P2P adjacencies with 3-way-handshake only.

`$ sudo bngblaster-cli run.sock isis-adjacencies`
```json
{
    "status": "ok",
    "code": 200,
    "isis-adjacencies": [
        {
            "interface": "eth1",
            "type": "P2P",
            "level": "L1",
            "instance-id": 2,
            "adjacency-state": "Up",
            "peer": {
                "system-id": "0100.1001.0022"
            }
        },
        {
            "interface": "eth2",
            "type": "P2P",
            "level": "L1",
            "instance-id": 1,
            "adjacency-state": "Up",
            "peer": {
                "system-id": "0100.1001.0021"
            }
        }
    ]
}
```

## Database

The BNG Blaster distinguishes between three different source types of 
LSP entries in the ISIS database. 

The type `self` is used for the self originated LSP describing the own 
BNG Blaster ISIS instance. LSP entries of type `adjacency` are learned
via ISIS adjacencies. The type `external` is used for those LSP entries 
learned via MRT files or injected via `isis-lsp-update` command.

`$ sudo bngblaster-cli run.sock isis-database instance 1 level 1`
```json
{
    "status": "ok",
    "code": 200,
    "isis-database": [
        {
            "id": "0000.0000.0001.00-00",
            "seq": 1,
            "lifetime": 65535,
            "lifetime-remaining": 65529,
            "source-type": "external"
        },
        {
            "id": "0100.1001.0011.00-00",
            "seq": 2,
            "lifetime": 65535,
            "lifetime-remaining": 65507,
            "source-type": "self"
        },
        {
            "id": "0100.1001.0021.00-00",
            "seq": 2,
            "lifetime": 65524,
            "lifetime-remaining": 65506,
            "source-type": "adjacency",
            "source-system-id": "0100.1001.0021"
        },
        {
            "id": "0100.1001.0022.00-00",
            "seq": 2,
            "lifetime": 65524,
            "lifetime-remaining": 65506,
            "source-type": "adjacency",
            "source-system-id": "0100.1001.0021"
        }
    ]
}
```

The BNG Blaster automatically purges all LSP's of type
`self` and `external` during teardown. This is done by
generating LSP's with a newer sequence numbers and lifetime
of 30 seconds only. This lifetime is enough to flood the purge
LSP over te whole network under test. 

## Flooding

The BNG Blaster floods LSP's received to all other active
adjacencies of the ISIS instance except to those with peer
system-id equal to the source system-id of the LSP.

## Limitations

Currently only ISIS P2P links are supported. There is also
no support for route leaking between levels. 

## MRT Files

The BNG Blaster is able to load LSP's from a MRT file as defined in 
[RFC6396](https://datatracker.ietf.org/doc/html/rfc6396).

```text
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                           Timestamp                           |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |             Type              |            Subtype            |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                             Length                            |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                      Message... (variable)
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

The message field contains the complete ISIS LSP PDU including 
the ISIS common header starting with `0x83`. 

Those files can be loaded at startup via configuration option 
`"isis": { "external": { "mrt-file": "<file>" } }` or alternative
via `isis-load-mrt` command. 

`$ sudo bngblaster-cli run.sock isis-load-mrt file test.mrt instance 1`

## LSP Update Command

It is also possible to inject external LSP's using the `isis-lsp-update`
command. 

The command expects a list of hex encoded PDU's including 
the ISIS common header starting with `0x83`, 

`$ cat command.json | jq .`
```json
{
    "command": "isis-lsp-update",
    "arguments": {
        "instance": 1,
        "pdu": [
            "831b0100120100000021ffff010203040506000000000003c0d103010403490001", 
            "831b0100120100000021ffff010203040506000100000003bad603010403490001"
        ]
    }
}
```

## LSP Update via Scapy 

The following example shows how to generate LSP's via Scapy 
and inject them using the `isis-lsp-update` command. 

```python
import sys
import socket
import os
import json

from scapy.contrib.isis import *

def error(*args, **kwargs):
    """print error and exit"""
    print(*args, file=sys.stderr, **kwargs)
    sys.exit(1)


def execute_command(socket_path, request):
    if os.path.exists(socket_path):
        client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        try:
            client.connect(socket_path)
            client.send(json.dumps(request).encode('utf-8'))
            data = ""
            while True:
                junk = client.recv(1024)
                if junk:
                    data += junk.decode('utf-8')
                else:
                    break
            print(json.dumps(json.loads(data), indent=4))
        except Exception as e:
            error(e)
        finally:
            client.close()
    else:
        error("socket %s not found" % socket_path)


def main():
    """main function"""
    socket_path = sys.argv[1]

    command = {
        "command": "isis-lsp-update",
        "arguments": {
            "instance": 1, 
            "pdu": []
        }    
    }

    tlvs = ISIS_AreaTlv(areas=ISIS_AreaEntry(areaid='49.0001'))
    pdu = ISIS_CommonHdr()/ISIS_L1_LSP(lifetime=65535, lspid='0102.0304.0506.00-00', seqnum=3, tlvs=tlvs)
    command["arguments"]["pdu"].append(pdu.build().hex())

    pdu = ISIS_CommonHdr()/ISIS_L1_LSP(lifetime=65535, lspid='0102.0304.0506.00-01', seqnum=3, tlvs=tlvs)
    command["arguments"]["pdu"].append(pdu.build().hex())

    execute_command(socket_path, command)


if __name__ == "__main__":
    main()

```