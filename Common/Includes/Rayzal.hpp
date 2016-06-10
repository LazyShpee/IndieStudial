#ifndef RAYZAL_HPP_
# define RAYZAL_HPP_

# include <thread>
# include <mutex>

# include "IncludeRaknet.hpp"
# include "Entity.hpp"
# include "Peer.hpp"

# define OK_CONNECTION 1

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

#pragma pack(push, 1)
  struct BasicPacket
  {
    packet_type PacketType;
    irr::u32 uuid;
  };
#pragma pack(pop)
  
#pragma pack(push, 1)
  struct EntityPacket: public BasicPacket
  {
    short EntityType;
	float px;
	float py;
	float pz;
	float rx;
	float ry;
	float rz;
  };
#pragma pack(pop)

#pragma pack(push, 1)
  struct InputPacket : public BasicPacket
  {
	  irr::u32 input;
  };
#pragma pack(pop)

#pragma pack(push, 1)
  struct PlayerInfoPacket : public BasicPacket
  {
	  char nick[32];
  };
#pragma pack(pop)

#pragma pack(push, 1)
  struct GameInfoPacket
  {
    char map_name[32];
    PlayerInfoPacket player_list[NB_PLAYERS];
  };
#pragma pack(pop)

  void SendPacket(BasicPacket const *);

  class ListenerThread
  {
    std::thread *_thread;
    iscene::ISceneManager *_smgr;
    rayzal::Peer *_peer;
    int _queue;
    int _wait;
  public:
    static std::mutex mutex;
  public:
    ListenerThread(rayzal::Peer *peer);
    ListenerThread(iscene::ISceneManager *smgr, rayzal::Peer *peer);
    ~ListenerThread(void);
  private:
    void loop(void);
  public:
    bool getQueue(void) const;
    int wait_connection(void) const
  };
}

#endif // RAYZAL_HPP_
