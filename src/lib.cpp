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

#include "ipfs/ipfs_embedded.h"

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

const char* get_api_version(void)
{
  return IPSF_API_VERSION;
}

void init(unsigned int bits, const char* passphrase, bool force)
{
  std::stringstream cmd;

  cmd << "init";
  cmd << " -b " << bits;
  if (passphrase && *passphrase != '\0')
    cmd << " -p " << passphrase;
  cmd << " -f " << (force ? "true" : "false");

  invoke(cmd.str());
}

void add(const char* path, bool recursive, bool quiet, bool progress, bool wrap_with_directory, bool trickle)
{
  std::stringstream cmd;

  cmd << "add";
  cmd << " " << (path ? path : "");
  cmd << " -r " << (recursive ? "true" : "false");
  cmd << " -q " << (quiet ? "true" : "false");
  cmd << " -p " << (progress ? "true" : "false");
  cmd << " -w " << (wrap_with_directory ? "true" : "false");
  cmd << " -t " << (trickle ? "true" : "false");

  invoke(cmd.str());
}

void cat(const char* ipfs_path)
{
  std::stringstream cmd;

  cmd << "cat";
  cmd << " " << (ipfs_path ? ipfs_path : "");

  invoke(cmd.str());
}

void get(const char* ipfs_path, const char* output, bool archive, bool compress, unsigned int compression_level)
{
  std::stringstream cmd;

  cmd << "get";
  cmd << " " << (ipfs_path ? ipfs_path : "");
  if (output && *output != '\0')
    cmd << " -o " << output;
  cmd << " -a " << (archive ? "true" : "false");
  cmd << " -C " << (compress ? "true" : "false");
  if (compress)
    cmd << " -l " << compression_level;

  invoke(cmd.str());
}

void ls(const char* ipfs_path)
{
  std::stringstream cmd;

  cmd << "ls";
  cmd << " " << (ipfs_path ? ipfs_path : "");

  invoke(cmd.str());
}

void refs(const char* ipfs_path, const char* format, bool edges, bool unique, bool recursive)
{
  std::stringstream cmd;

  cmd << "refs";
  cmd << " " << (ipfs_path ? ipfs_path : "");
  if (format && *format != '\0')
    cmd << " -format " << format;
  cmd << " -e " << (edges ? "true" : "false");
  cmd << " -u " << (unique ? "true" : "false");
  cmd << " -r " << (recursive ? "true" : "false");

  invoke(cmd.str());
}

void refs_local(void)
{
  std::stringstream cmd;

  cmd << "refs local";

  invoke(cmd.str());
}

void block_put(const char* data)
{
  std::stringstream cmd;

  cmd << "block put";
  cmd << " " << (data ? data : "");

  invoke(cmd.str());
}

void block_stat(const char* key)
{
  std::stringstream cmd;

  cmd << "block stat";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void block_get(const char* key)
{
  std::stringstream cmd;

  cmd << "block get";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void object_data(const char* key)
{
  std::stringstream cmd;

  cmd << "object data";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void object_links(const char* key)
{
  std::stringstream cmd;

  cmd << "object links";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void object_get(const char* key)
{
  std::stringstream cmd;

  cmd << "object get";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void object_put(const char* data)
{
  std::stringstream cmd;

  cmd << "object put";
  cmd << " " << (data ? data : "");

  invoke(cmd.str());
}

void object_stat(const char* key)
{
  std::stringstream cmd;

  cmd << "object stat";
  cmd << " " << (key ? key : "");

  invoke(cmd.str());
}

void daemon(bool init, const char* routing, bool mount, bool writable, const char* mount_ipfs, const char* mount_ipns)
{
  std::stringstream cmd;

  cmd << "daemon";
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

void mount(const char* f, const char* n)
{
  std::stringstream cmd;

  cmd << "mount";
  if (f && *f != '\0')
    cmd << " -f " << f;
  if (n && *n != '\0')
    cmd << " -n " << n;

  invoke(cmd.str());
}

void name_publish(const char* name, const char* ipfs_path)
{
  std::stringstream cmd;

  cmd << "name publish";
  if (name && *name != '\0')
    cmd << " " << name;
  if (ipfs_path && *ipfs_path != '\0')
    cmd << " " << ipfs_path;

  invoke(cmd.str());
}

void name_resolve(const char* name)
{
  std::stringstream cmd;

  cmd << "name resolve";
  if (name && *name != '\0')
    cmd << " " << name;

  invoke(cmd.str());
}

void pin_rm(const char* ipfs_path, bool recursive)
{
  std::stringstream cmd;

  cmd << "pin rm";
  if (ipfs_path && *ipfs_path != '\0')
    cmd << " " << ipfs_path;
  cmd << " -r " << (recursive ? "true" : "false");

  invoke(cmd.str());
}

void pin_ls(const char* type)
{
  std::stringstream cmd;

  cmd << "pin ls";
  if (type && *type != '\0')
    cmd << " -t " << type;

  invoke(cmd.str());
}

void pin_add(const char* ipfs_path, bool recursive)
{
  std::stringstream cmd;

  cmd << "pin add";
  if (ipfs_path && *ipfs_path != '\0')
    cmd << " " << ipfs_path;
  cmd << " -r " << (recursive ? "true" : "false");

  invoke(cmd.str());
}

void repo_gc(bool quiet)
{
  std::stringstream cmd;

  cmd << "repo gc";
  cmd << " -q " << (quiet ? "true" : "false");

  invoke(cmd.str());
}

void network_id(const char* peer_id)
{
  std::stringstream cmd;

  cmd << "id";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;

  invoke(cmd.str());
}

void bootstrap_list(void)
{
  std::stringstream cmd;

  cmd << "bootstrap list";

  invoke(cmd.str());
}

void bootstrap_add(const char* peer, bool default_nodes)
{
  std::stringstream cmd;

  cmd << "bootstrap add";
  if (peer && *peer != '\0')
    cmd << " " << peer;
  cmd << " -default " << (default_nodes ? "true" : "false");

  invoke(cmd.str());
}

void bootstrap_rm(const char* peer, bool all)
{
  std::stringstream cmd;

  cmd << "bootstrap rm";
  if (peer && *peer != '\0')
    cmd << " " << peer;
  cmd << " -all " << (all ? "true" : "false");

  invoke(cmd.str());
}

void swarm_disconnect(const char* address)
{
  std::stringstream cmd;

  cmd << "swarm disconnect";
  if (address && *address != '\0')
    cmd << " " << address;

  invoke(cmd.str());
}

void swarm_peers(void)
{
  std::stringstream cmd;

  cmd << "swarm peers";

  invoke(cmd.str());
}

void swarm_addrs(void)
{
  std::stringstream cmd;

  cmd << "swarm addrs";

  invoke(cmd.str());
}

void swarm_connect(const char* address)
{
  std::stringstream cmd;

  cmd << "swarm connect";
  if (address && *address != '\0')
    cmd << " " << address;

  invoke(cmd.str());
}

void dht_query(const char* peer_id, bool verbose)
{
  std::stringstream cmd;

  cmd << "dht query";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;
  cmd << " -v " << (verbose ? "true" : "false");

  invoke(cmd.str());
}

void dht_findprovs(const char* key, bool verbose)
{
  std::stringstream cmd;

  cmd << "dht findprovs";
  if (key && *key != '\0')
    cmd << " " << key;
  cmd << " -v " << (verbose ? "true" : "false");

  invoke(cmd.str());
}

void dht_findpeer(const char* peer_id)
{
  std::stringstream cmd;

  cmd << "dht findpeer";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;

  invoke(cmd.str());
}

void ping(const char* peer_id, unsigned int count)
{
  std::stringstream cmd;

  cmd << "ping";
  if (peer_id && *peer_id != '\0')
    cmd << " " << peer_id;
  if (count > 0)
    cmd << " -n " << count;

  invoke(cmd.str());
}

void diag_net(unsigned int timeout)
{
  std::stringstream cmd;

  cmd << "diag net";
  cmd << " -timeout " << timeout;

  invoke(cmd.str());
}

void config_get(const char* key)
{
  std::stringstream cmd;

  cmd << "config";
  if (key && *key != '\0')
    cmd << " " << key;

  invoke(cmd.str());
}

void config_set(const char* key, const char* value)
{
  std::stringstream cmd;

  cmd << "config";
  if (key && *key != '\0')
    cmd << " " << key;
  if (value && *value != '\0')
    cmd << " " << value;

  invoke(cmd.str());
}

void config_show(void)
{
  std::stringstream cmd;

  cmd << "config show";

  invoke(cmd.str());
}

void config_edit(void)
{
  std::stringstream cmd;

  cmd << "config edit";

  invoke(cmd.str());
}

void config_replace(const char* file)
{
  std::stringstream cmd;

  cmd << "config replace";
  if (file && *file != '\0')
    cmd << " " << file;

  invoke(cmd.str());
}

void version(void)
{
  std::stringstream cmd;

  cmd << "version";

  invoke(cmd.str());
}

} // extern "C"
