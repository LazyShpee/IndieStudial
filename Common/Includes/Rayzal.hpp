#ifndef RAYZAL_HPP_
# define RAYZAL_HPP_

# include <thread>
# include <mutex>

# include "IncludeRaknet.hpp"
# include "Entity.hpp"
# include "Peer.hpp"

namespace rayzal
{
  enum packet_type
    {
      // tcp (client -> server)
      ID_ENTER_QUEUE = ID_USER_PACKET_ENUM + 1,
      ID_PLAYER_INFOS,

      // tcp (server -> client)
      ID_ENTER_GAME,
      ID_GAME_INFOS,

      // udp (client -> server)
      ID_INPUT,

      // udp (server -> client)
      ID_ENTITY,
      ID_DELETE
    };

  struct BasicPacket
  {
    packet_type type;
    irr::u32 uuid;
  };

  struct EntityPacket: public BasicPacket
  {
    short EntityType;
  };

  struct InputPacket: public BasicPacket
  {
    irr::u32 input;
  };

  void SendPacket(BasicPacket const *);

  class ListenerThread
  {
    std::thread *_thread;
    iscene::ISceneManager *_smgr;
    rayzal::Peer *_peer;
  public:
    static std::mutex mutex;
  public:
    ListenerThread(rayzal::Peer *peer);
    ListenerThread(iscene::ISceneManager *smgr, rayzal::Peer *peer);
    ~ListenerThread(void);
  private:
    void loop(void);
  };
}

#endif // RAYZAL_HPP_
