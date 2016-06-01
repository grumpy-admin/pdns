#pragma once
#include "config.h"

#include <mutex>

#include "iputils.hh"

#ifdef HAVE_EBPF

class BPFFilter
{
public:
  BPFFilter(uint32_t maxV4Addresses, uint32_t maxV6Addresses, uint32_t maxQNames);
  ~BPFFilter();
  void addSocket(int sock);
  void block(const ComboAddress& addr);
  void block(const DNSName& qname, uint16_t qtype=255);
  void unblock(const ComboAddress& addr);
  void unblock(const DNSName& qname, uint16_t qtype=255);
  std::vector<std::pair<ComboAddress, uint64_t> > getAddrStats();
  std::vector<std::tuple<DNSName, uint16_t, uint64_t> > getQNameStats();
private:
  std::mutex d_mutex;
  uint32_t d_maxV4;
  uint32_t d_maxV6;
  uint32_t d_maxQNames;
  uint32_t d_v4Count{0};
  uint32_t d_v6Count{0};
  uint32_t d_qNamesCount{0};
  int d_v4map{-1};
  int d_v6map{-1};
  int d_qnamemap{-1};
  int d_filter{-1};
};

#endif /* HAVE_EBPF */
