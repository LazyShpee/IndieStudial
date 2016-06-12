#ifndef RAYZAL_HPP_
# define RAYZAL_HPP_

# include <thread>
# include <mutex>

# include "IncludeRaknet.hpp"
# include "Peer.hpp"
# include "Constants.hpp"

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
      ID_DELETE,
      ID_SOUND
    };

#pragma pack(push, 1)
  struct BasicPacket
  {
    packet_type PacketType;
    irr::u32 uuid;
  };
#pragma pack(pop)

#pragma pack(push, 1)
  struct SoundPacket: public BasicPacket
  {
    int sound_id;
    bool loop;
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
    char nick[SHORT_BUFFER];
    int life;
    irr::u32 car_model[SHORT_BUFFER];
    char car_name[SHORT_BUFFER];
    char car_desc[1024];
  };
#pragma pack(pop)

#pragma pack(push, 1)
  struct GameInfoPacket: public BasicPacket
  {
    char map_name[SHORT_BUFFER];
    PlayerInfoPacket player_list[NB_PLAYERS];
  };
#pragma pack(pop)

  class ListenerThread
  {
    std::thread *_thread;
    iscene::ISceneManager *_smgr;
    rayzal::Peer *_peer;
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
    int wait_connection(void) const;
    void join(void);
  };
}

#endif // RAYZAL_HPP_
