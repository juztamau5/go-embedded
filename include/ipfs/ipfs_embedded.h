/*
 *    Copyright (C) 2015 juztamau5
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef __IPSF_EMBEDDED_H__
#define __IPSF_EMBEDDED_H__

#include "ipfs_types.h"

#ifdef __cplusplus
extern "C"
{
#endif
  /*!
   * \brief Get the IPSF_API_VERSION used during compilation
   * \return IPSF_API_VERSION from ipfs_types.h
   */
  const char* get_api_version(void);

  /// @name Basic commands
  ///{
  /*!
   * \brief Initialize IPSF local configuration
   *
   * \param bits Number of bits to use in the RSA private key
   * \param passphrase The passphrase for encrypting the private key, or empty for no encryption
   * \param force Overwrite the existing config (if it exists)
   *
   * Initializes IPFS configuration files and generates a new keypair.
   */
  void init(unsigned int bits, const char* passphrase, bool force);

  /*!
   * \brief Add an object to IPFS
   *
   * \param path The path to a file to be added to IPSF
   * \param recursive Add directory paths recursively
   * \param quiet Write minimal output
   * \param progress Stream progress data
   * \param wrap_with_directory Wrap files with a directory object
   * \param trickle Use trickle-DAG format for DAG generation
   *
   * Adds contents of <path> to IPFS. Use recursion to add directories. Note
   * that directories are added recursively, to form the IPFS merkle-DAG. A
   * smarter partial add with a staging area (like git) remains to be
   * implemented.
   */
  void add(const char* path, bool recursive, bool quiet, bool progress, bool wrap_with_directory, bool trickle);

  /*!
   * \brief Show IPFS object data
   *
   * \param ipfs_path The path to the IPSF object(s) to be output
   *
   * Retrieves the object named by <ipfs_path> and outputs the data it contains.
   */
  void cat(const char* ipfs_path);

  /*!
   * \brief Download IPFS objects
   *
   * \param ipfs_path The path to the IPFS object(s) to be output
   * \param output The path where output should be stored
   * \param compress Compress the output with GZIP compression
   * \param compression_level The level of compression (1-9)
   *
   * Retrieves the object named by <ipfs_path> and stores the data to disk.
   *
   * By default, the output will be stored at ./<ipfs_path>, but an alternate
   * path can be specified with <output>.
   *
   * To output a TAR archive instead of unpacked files, set <archive> to true.
   *
   * To compress the output with GZIP compression, set <compress> to true. You
   * may also specify the level of compression in the range 1-9.
   */
  void get(const char* ipfs_path, const char* output, bool archive, bool compress, unsigned int compression_level);

  /*!
   * \brief List links from an object
   *
   * \param ipfs_path The path to the IPFS object(s) to list links from
   *
   * Retrieves the object named by <ipfs_path> and displays the links it
   * contains, with the following format:
   *
   *     <link base58 hash> <link size in bytes> <link name>
   */
  void ls(const char* ipfs_path);

  /*!
   * \brief List hashes of links from an object
   *
   * \param ipfs_path Path to the object(s) to list refs from
   * \param format Emit edges with given format. tokens: <src> <dst> <linkname>
   * \param edges Emit edge format: `<from> -> <to>`
   * \param unique Omit duplicate refs from output
   * \param recursive Recursively list links of child nodes
   *
   * Retrieves the object named by <ipfs_path> and displays the link hashes it
   * contains, with the following format:
   *
   *     <link base58 hash>
   *
   * Note: list all refs recursively by setting <recursive> to true.
   */
  void refs(const char* ipfs_path, const char* format, bool edges, bool unique, bool recursive);

  /*!
   * \brief Lists all local references
   *
   * Displays the hashes of all local objects.
   */
  void refs_local(void);
  ///}

  /// @name Data structure commands
  ///{
  /*!
   * \brief Stores input as an IPFS block
   *
   * \param data The data to be stored as an IPFS block
   *
   * This is a plumbing command for storing raw IPFS blocks.
   */
  void block_put(const char* data);

  /*!
   * \brief Print information of a raw IPFS block
   *
   * \param key The base58 multihash of an existing block to get
   *
   * This is a plumbing command for retrieving information on raw IPFS blocks.
   * It outputs the following to stdout:
   *
   *    Key  - the base58 encoded multihash
   *    Size - the size of the block in bytes
   */
  void block_stat(const char* key);

  /*!
   * \brief Get a raw IPFS block
   *
   * \param key The base58 multihash of an existing block to get
   *
   * This is a plumbing command for retrieving raw IPSF blocks.
   */
  void block_get(const char* key);

  /*!
   * \brief Outputs the raw bytes in an IPFS object
   *
   * \param key Key of the object to retrieve, in base58-encoded multihash format
   *
   * This is a plumbing command for retrieving the raw bytes stored in a DAG
   * node. It outputs to stdout, and <key> is a base58 encoded multihash.
   */
  void object_data(const char* key);

  /*!
   * \brief Outputs the links pointed to by the specified object
   *
   * \param key Key of the object to retrieve, in base58-encoded multihash format
   *
   * This is a plumbing command for retreiving the links from a DAG node. It
   * outputs to stdout, and <key> is a base58 encoded multihash.
   */
  void object_links(const char* key);

  /*!
   * \brief Get and serialize the DAG node named by <key>
   *
   * \param key Key of the object to retrieve (in base58-encoded multihash format)
   *
   * This is a plumbing command for retreiving DAG nodes. It serializes the DAG
   * node to the format specified <encoding>. It outputs to stdout, and <key> is
   * a base58 encoded multihash.
   */
  void object_get(const char* key);

  /*!
   * \brief Stores input as a DAG object, outputs its key
   *
   * \param data Data to be stored as a DAG object
   *
   * This is a plumbing command for storing DAG nodes. It reads from stdin, and
   * the output is a base58 encoded multihash.
   */
  void object_put(const char* data);

  /*!
   * \brief Get stats for the DAG node named by <key>
   *
   * \param key Key of the object to retrieve (in base58-encoded multihash format)
   *
   * This is a plumbing command to print DAG node statistics. <key> is a
   * base58-encoded multihash. It outputs to stdout:
   *
   *    NumLinks        int number of links in link table
   *    BlockSize       int size of the raw, encoded data
   *    LinksSize       int size of the links segment
   *    DataSize        int size of the data segment
   *    CumulativeSize  int cumulative size of object and its references
   */
  void object_stat(const char* key);
  ///}

  /// @name Advanced commands
  ///{
  /*!
   * \brief Start a long-running daemon process
   *
   * \param init Initialize IPFS with default settings if not already initialized
   * \param routing Overrides the routing option (dht, supernode)
   * \param mount Mounts IPFS to the filesystem
   * \param writable Enable writing objects (with POST, PUT and DELETE)
   * \param mount_ipfs Path to the mountpoint for IPFS (if <mount> is true)
   * \param mount_ipns Path to the mountpoint for IPNS (if <mount> is true)
   *
   * This runs a persistent IPFS daemon that can serve commands over the
   * network. Most applications that use IPFS will do so by communicating with
   * a daemon over the HTTP API.
   */
  void daemon(bool init, const char* routing, bool mount, bool writable, const char* mount_ipfs, const char* mount_ipns);

  /*!
   * \brief Mount an IPFS read-only mountpoint
   *
   * \param f The path where IPFS should be mounted
   * \param n The path where IPNS should be mounted
   *
   * Mount IPFS at a read-only mountpoint on the OS (default: /ipfs and /ipns).
   * All IPFS objects will be accessible under that directory. Note that the
   * root will not be listable, as it is virtual. Access known paths directly.
   *
   * You may have to create /ipfs and /ipns before calling mount():
   *
   *    $ sudo mkdir /ipfs /ipns
   *    $ sudo chown `whoami` /ipfs /ipns
   */
  void mount(const char* f, const char* n);

  /*!
   * \brief Publish an object to IPNS
   *
   * \param name The IPNS name to publish to
   * \param ipfs_path IPFS path of the object to be published at <name>
   *
   * IPNS is a PKI namespace, where names are the hashes of public keys, and the
   * private key enables publishing new (signed) values.
   */
  void name_publish(const char* name, const char* ipfs_path);

  /*!
   * \brief Get the value currently published at an IPNS name
   *
   * \param name The IPNS name to resolve. Defaults to your node's peerID
   */
  void name_resolve(const char* name);

  /*!
   * \brief Unpin an object from local storage
   *
   * \param ipfs_path Path to object(s) to be unpinned
   * \param recursive Recursively unpin the object linked to by the specified object(s)
   *
   * Removes the pin from the given object allowing it to be garbage collected
   * if needed.
   */
  void pin_rm(const char* ipfs_path, bool recursive);

  /*!
   * \brief List objects pinned to local storage
   *
   * \param type The type of pinned keys to list
   *
   * Returns a list of hashes of pinned objects. Objects that are indirectly or
   * recursively pinned are not included in the list.
   *
   * Use <type> to specify the type of pinned keys to list. Valid values are:
   *    - "direct" (default)
   *    - "indirect"
   *    - "recursive"
   *    - "all"
   */
  void pin_ls(const char* type);

  /*!
   * \brief Pin objects to local storage
   *
   * \param ipfs_path Path to object(s) to be pinned
   * \param recursive Recursively pin the object linked to by the specified object(s)
   *
   * Retrieves the object named by <ipfs_path> and stores it locally on disk.
   */
  void pin_add(const char* ipfs_path, bool recursive);

  /*!
   * \brief Perform a garbage collection sweep on the repo
   *
   * \param quiet If true, write minimal output
   *
   * This is a plumbing command that will sweep the local set of stored objects
   * and remove ones that are not pinned in order to reclaim hard disk space.
   */
  void repo_gc(bool quiet);
  ///}

  /// @name Network commands
  ///{
  /*!
   * \brief Show IPFS Node ID info
   *
   * \param peer_id peer.ID of node to look up, or empty for all peers
   *
   * Prints out information about the specified peer, or if no peer is
   * specified, prints out local peers info.
   */
  void network_id(const char* peer_id);

  /*!
   * \brief Show peers in the bootstrap list
   *
   * Peers are output in the format '<multiaddr>/<peerID>'.
   */
  void bootstrap_list(void);

  /*!
   * \brief Add peers to the bootstrap list
   *
   * \param peer A peer to add to the bootstrap list (in the format '<multiaddr>/<peerID>')
   * \param default_nodes If true, add default bootstrap nodes
   *
   * Outputs a list of peers that were added (that weren't already in the
   * bootstrap list).
   *
   * SECURITY WARNING:
   *
   * The bootstrap command manipulates the "bootstrap list", which contains
   * the addresses of bootstrap nodes. These are the *trusted peers* from
   * which to learn about other peers in the network. Only edit this list
   * if you understand the risks of adding or removing nodes from this list.
   */
  void bootstrap_add(const char* peer, bool default_nodes);

  /*!
   * \brief Removes peers from the bootstrap list
   *
   * \param peer A peer to add to the bootstrap list (in the format '<multiaddr>/<peerID>')
   * \param all If true, remove all bootstrap peers
   *
   * Outputs the list of peers that were removed.
   *
   * SECURITY WARNING:
   *
   * The bootstrap command manipulates the "bootstrap list", which contains
   * the addresses of bootstrap nodes. These are the *trusted peers* from
   * which to learn about other peers in the network. Only edit this list
   * if you understand the risks of adding or removing nodes from this list.
   *
   */
  void bootstrap_rm(const char* peer, bool all);

  /*!
   * \brief Close connection to a given address
   *
   * \param address Address of peer to connect to
   *
   * This closes a connection to a peer address. The address format is an IPFS
   * multiaddr:
   *
   * swarm disconnect("/ip4/104.131.131.82/tcp/4001/ipfs/QmaCpDMGvV2BGHeYERUEnRQAwe3N8SzbUtfsmvsqQLuvuJ");
   */
  void swarm_disconnect(const char* address);

  /*!
   * \brief List peers with open connections
   *
   * This lists the set of peers this node is connected to.
   */
  void swarm_peers(void);

  /*!
   * \brief List known addresses. Useful to debug.
   *
   * This lists all addresses this node is aware of.
   */
  void swarm_addrs(void);

  /*!
   * \brief Open connection to a given address
   *
   * \param address Address of peer to connect to
   *
   * This opens a connection to a peer address. The address format is an IPFS
   * multiaddr:
   *
   * swarm_connect("/ip4/104.131.131.82/tcp/4001/ipfs/QmaCpDMGvV2BGHeYERUEnRQAwe3N8SzbUtfsmvsqQLuvuJ")
   */
  void swarm_connect(const char* address);

  /*!
   * \brief Run a 'findClosestPeers' query through the DHT
   *
   * \param peer_id The peer ID to run the query against
   * \param verbose If true, write extra information
   */
  void dht_query(const char* peer_id, bool verbose);

  /*!
   * \brief Run a 'FindProviders' query through the DHT
   *
   * \param key The key to find providers for
   * \param verbose If true, write extra information
   *
   * The 'FindProviders' query will return a list of peers who are able to
   * provide the value requested.
   */
  void dht_findprovs(const char* key, bool verbose);

  /*!
   * \brief Run a 'FindPeer' query through the DHT
   *
   * \param peer_id The peer to search for
   */
  void dht_findpeer(const char* peer_id);

  /*!
   * \brief Measure the latency of a connection
   *
   * \param peer_id ID of peer to be pinged
   * \param count The number of ping messages to send
   *
   * This is a tool to test sending data to other nodes. It finds nodes via the
   * routing system, send pings, wait for pongs, and print out round-trip
   * latency information.
   */
  void ping(const char* peer_id, unsigned int count);

  /*!
   * \brief Generates a network diagnostics report
   *
   * \param timeout Diagnostic timeout duration
   *
   * Sends out a message to each node in the network recursively requesting a
   * listing of data about them including number of connected peers and
   * latencies between them.
   *
   * The given timeout will be decremented 2s at every network hop, ensuring
   * peers try to return their diagnostics before the initiator's timeout. If
   * the timeout is too small, some peers may not be reached. 30s and 60s are
   * reasonable timeout values, though network vary. The default timeout is 20
   * seconds.
   */
  void diag_net(unsigned int timeout);
  ///}

  /// @name Tool commands
  ///{
  /*!
   * \brief Get IPFS config values
   *
   * \param key The key of the config entry (e.g. "Addresses.API")
   *
   * This controls configuration variables. The configuration values are stored
   * in a config file inside your IPFS repository.
   */
  void config_get(const char* key);

  /*!
   * \brief Set IPFS config values
   *
   * \param key The key of the config entry (e.g. "Addresses.API")
   * \param value The value to set the config entry to
   */
  void config_set(const char* key, const char* value);

  /*!
   * \brief Outputs the content of the config file
   *
   * WARNING: Your private key is stored in the config file, and it will be
   * included in the output of this command.
   */
  void config_show(void);

  /*!
   * \brief Opens the config file for editing in $EDITOR
   *
   * To use config_edit(), you must have the $EDITOR environment variable set
   * to your preferred text editor.
   */
  void config_edit(void);

  /*!
   * \brief Replaces the config with <file>
   *
   * \param file The file to use as the new config
   *
   * Make sure to back up the config file first if neccessary, this operation
   * can't be undone.
   */
  void config_replace(const char* file);

  /*!
   * \brief Show IPFS version information
   */
  void version(void);
  ///}
#ifdef __cplusplus
}
#endif

#endif // __IPSF_EMBEDDED_H__
