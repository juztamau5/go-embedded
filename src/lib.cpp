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

#include "ipfs/libipfs.h"

// Go generated include file
#include "ipfs.h"

#include <sstream>
#include <string>

namespace IPSF
{
  void invoke(const std::string& cmd)
  {
    GoString str;
    str.p = const_cast<char*>(cmd.c_str());
    str.n = static_cast<GoInt>(cmd.length());
    runMain(str);
  }
}

using namespace IPSF;

extern "C"
{

void ipfs_init(unsigned int bits, const char* passphrase, bool force)
{
  std::stringstream cmd;

  cmd << "ipfs init";
  cmd << " -b " << bits;
  if (passphrase && *passphrase != '\0')
    cmd << " -p " << passphrase;
  cmd << " -f " << (force ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_add(const char* path, bool recursive, bool quiet, bool progress, bool wrap_with_directory, bool trickle)
{
  std::stringstream cmd;

  cmd << "ipfs add";
  cmd << " " << (path ? path : "");
  cmd << " -r " << (recursive ? "true" : "false");
  cmd << " -q " << (quiet ? "true" : "false");
  cmd << " -p " << (progress ? "true" : "false");
  cmd << " -w " << (wrap_with_directory ? "true" : "false");
  cmd << " -t " << (trickle ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_cat(const char* ipfs_path)
{
  std::stringstream cmd;

  cmd << "ipfs cat";
  cmd << " " << (ipfs_path ? ipfs_path : "");

  invoke(cmd.str());
}

void ipfs_get(const char* ipfs_path, const char* output, bool archive, bool compress, unsigned int compression_level)
{
  std::stringstream cmd;

  cmd << "ipfs get";
  cmd << " " << (ipfs_path ? ipfs_path : "");
  if (output && *output != '\0')
    cmd << " -o " << output;
  cmd << " -a " << (archive ? "true" : "false");
  cmd << " -C " << (compress ? "true" : "false");
  if (compress)
    cmd << " -l " << compression_level;

  invoke(cmd.str());
}

void ipfs_ls(const char* ipfs_path)
{
  std::stringstream cmd;

  cmd << "ipfs ls";
  cmd << " " << (ipfs_path ? ipfs_path : "");

  invoke(cmd.str());
}

void ipfs_refs(const char* ipfs_path, const char* format, bool edges, bool unique, bool recursive)
{
  std::stringstream cmd;

  cmd << "ipfs refs";
  cmd << " " << (ipfs_path ? ipfs_path : "");
  if (format && *format != '\0')
    cmd << " -format " << format;
  cmd << " -e " << (edges ? "true" : "false");
  cmd << " -u " << (unique ? "true" : "false");
  cmd << " -r " << (recursive ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_refs_local(void)
{
  std::stringstream cmd;

  cmd << "ipfs refs local";

  invoke(cmd.str());
}

void ipfs_block_put(const char* data)
{
  std::stringstream cmd;

  cmd << "ipfs block put";
  cmd << " " << (data ? data : "");

  invoke(cmd.str());
}

void ipfs_block_stat(const char* key)
{
  std::stringstream cmd;

  cmd << "ipfs block stat";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void ipfs_block_get(const char* key)
{
  std::stringstream cmd;

  cmd << "ipfs block get";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void ipfs_object_data(const char* key)
{
  std::stringstream cmd;

  cmd << "ipfs object data";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void ipfs_object_links(const char* key)
{
  std::stringstream cmd;

  cmd << "ipfs object links";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void ipfs_object_get(const char* key)
{
  std::stringstream cmd;

  cmd << "ipfs object get";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void ipfs_object_put(const char* data)
{
  std::stringstream cmd;

  cmd << "ipfs object put";
  cmd << " " << (data ? data : "");

  invoke(cmd.str());
}

void ipfs_object_stat(const char* key)
{
  std::stringstream cmd;

  cmd << "ipfs object stat";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void ipfs_daemon(bool init, const char* routing, bool mount, bool writable, const char* mount_ipfs, const char* mount_ipns)
{
  std::stringstream cmd;

  cmd << "ipfs daemon";
  cmd << " -init " << (init ? "true" : "false");
  if (routing && *routing != '\0')
    cmd << " -routing " << routing;
  cmd << " -mount " << (mount ? "true" : "false");
  cmd << " -writable " << (writable ? "true" : "false");
  if (mount_ipfs && *mount_ipfs != '\0')
    cmd << " -mount-ipfs " << mount_ipfs;
  if (mount_ipns && *mount_ipns != '\0')
    cmd << " -mount-ipns " << mount_ipns;

  invoke(cmd.str());
}

void ipfs_mount(const char* f, const char* n)
{
  std::stringstream cmd;

  cmd << "ipfs mount";
  if (f && *f != '\0')
    cmd << " -f " << f;
  if (n && *n != '\0')
    cmd << " -n " << n;

  invoke(cmd.str());
}

void ipfs_name_publish(const char* name, const char* ipfs_path)
{
  std::stringstream cmd;

  cmd << "ipfs name publish";
  if (name && *name != '\0')
    cmd << " " << name;
  if (ipfs_path && *ipfs_path != '\0')
    cmd << " " << ipfs_path;

  invoke(cmd.str());
}

void ipfs_name_resolve(const char* name)
{
  std::stringstream cmd;

  cmd << "ipfs name resolve";
  if (name && *name != '\0')
    cmd << " " << name;

  invoke(cmd.str());
}

void ipfs_pin_rm(const char* ipfs_path, bool recursive)
{
  std::stringstream cmd;

  cmd << "ipfs pin rm";
  if (ipfs_path && *ipfs_path != '\0')
    cmd << " " << ipfs_path;
  cmd << " -r " << (recursive ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_pin_ls(const char* type)
{
  std::stringstream cmd;

  cmd << "ipfs pin ls";
  if (type && *type != '\0')
    cmd << " -t " << type;

  invoke(cmd.str());
}

void ipfs_pin_add(const char* ipfs_path, bool recursive)
{
  std::stringstream cmd;

  cmd << "ipfs pin add";
  if (ipfs_path && *ipfs_path != '\0')
    cmd << " " << ipfs_path;
  cmd << " -r " << (recursive ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_repo_gc(bool quiet)
{
  std::stringstream cmd;

  cmd << "ipfs repo gc";
  cmd << " -q " << (quiet ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_network_id(const char* peer_id)
{
  std::stringstream cmd;

  cmd << "ipfs id";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;

  invoke(cmd.str());
}

void ipfs_bootstrap_list(void)
{
  std::stringstream cmd;

  cmd << "ipfs bootstrap list";

  invoke(cmd.str());
}

void ipfs_bootstrap_add(const char* peer, bool default_nodes)
{
  std::stringstream cmd;

  cmd << "ipfs bootstrap add";
  if (peer && *peer != '\0')
    cmd << " " << peer;
  cmd << " -default " << (default_nodes ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_bootstrap_rm(const char* peer, bool all)
{
  std::stringstream cmd;

  cmd << "ipfs bootstrap rm";
  if (peer && *peer != '\0')
    cmd << " " << peer;
  cmd << " -all " << (all ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_swarm_disconnect(const char* address)
{
  std::stringstream cmd;

  cmd << "ipfs swarm disconnect";
  if (address && *address != '\0')
    cmd << " " << address;

  invoke(cmd.str());
}

void ipfs_swarm_peers(void)
{
  std::stringstream cmd;

  cmd << "ipfs swarm peers";

  invoke(cmd.str());
}

void ipfs_swarm_addrs(void)
{
  std::stringstream cmd;

  cmd << "ipfs swarm addrs";

  invoke(cmd.str());
}

void ipfs_swarm_connect(const char* address)
{
  std::stringstream cmd;

  cmd << "ipfs swarm connect";
  if (address && *address != '\0')
    cmd << " " << address;

  invoke(cmd.str());
}

void ipfs_dht_query(const char* peer_id, bool verbose)
{
  std::stringstream cmd;

  cmd << "ipfs dht query";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;
  cmd << " -v " << (verbose ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_dht_findprovs(const char* key, bool verbose)
{
  std::stringstream cmd;

  cmd << "ipfs dht findprovs";
  if (key && *key != '\0')
    cmd << " " << key;
  cmd << " -v " << (verbose ? "true" : "false");

  invoke(cmd.str());
}

void ipfs_dht_findpeer(const char* peer_id)
{
  std::stringstream cmd;

  cmd << "ipfs dht findpeer";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;

  invoke(cmd.str());
}

void ipfs_ping(const char* peer_id, unsigned int count)
{
  std::stringstream cmd;

  cmd << "ipfs ping";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;
  if (count > 0)
    cmd << " -n " << count;

  invoke(cmd.str());
}

void ipfs_diag_net(unsigned int timeout)
{
  std::stringstream cmd;

  cmd << "ipfs diag net";
  cmd << " -timeout " << timeout;

  invoke(cmd.str());
}

void ipfs_config_get(const char* key)
{
  std::stringstream cmd;

  cmd << "ipfs config";
  if (key && *key != '\0')
    cmd << " " << key;

  invoke(cmd.str());
}

void ipfs_config_set(const char* key, const char* value)
{
  std::stringstream cmd;

  cmd << "ipfs config";
  if (key && *key != '\0')
    cmd << " " << key;
  if (value && *value != '\0')
    cmd << " " << value;

  invoke(cmd.str());
}

void ipfs_config_show(void)
{
  std::stringstream cmd;

  cmd << "ipfs config show";

  invoke(cmd.str());
}

void ipfs_config_edit(void)
{
  std::stringstream cmd;

  cmd << "ipfs config edit";

  invoke(cmd.str());
}

void ipfs_config_replace(const char* file)
{
  std::stringstream cmd;

  cmd << "ipfs config replace";
  if (file && *file != '\0')
    cmd << " " << file;

  invoke(cmd.str());
}

void ipfs_version(void)
{
  std::stringstream cmd;

  cmd << "ipfs version";

  invoke(cmd.str());
}

} // extern "C"
