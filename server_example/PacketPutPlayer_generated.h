// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_PACKETPUTPLAYER_FPACKET_H_
#define FLATBUFFERS_GENERATED_PACKETPUTPLAYER_FPACKET_H_

#include "flatbuffers.h"

namespace fpacket {

struct PacketPutPlayer;

struct PacketPutPlayer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ID = 4,
    VT_X = 6,
    VT_Y = 8
  };
  int32_t id() const { return GetField<int32_t>(VT_ID, 0); }
  float x() const { return GetField<float>(VT_X, 0.0f); }
  float y() const { return GetField<float>(VT_Y, 0.0f); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_ID) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           verifier.EndTable();
  }
};

struct PacketPutPlayerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(int32_t id) { fbb_.AddElement<int32_t>(PacketPutPlayer::VT_ID, id, 0); }
  void add_x(float x) { fbb_.AddElement<float>(PacketPutPlayer::VT_X, x, 0.0f); }
  void add_y(float y) { fbb_.AddElement<float>(PacketPutPlayer::VT_Y, y, 0.0f); }
  PacketPutPlayerBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  PacketPutPlayerBuilder &operator=(const PacketPutPlayerBuilder &);
  flatbuffers::Offset<PacketPutPlayer> Finish() {
    auto o = flatbuffers::Offset<PacketPutPlayer>(fbb_.EndTable(start_, 3));
    return o;
  }
};

inline flatbuffers::Offset<PacketPutPlayer> CreatePacketPutPlayer(flatbuffers::FlatBufferBuilder &_fbb,
   int32_t id = 0,
   float x = 0.0f,
   float y = 0.0f) {
  PacketPutPlayerBuilder builder_(_fbb);
  builder_.add_y(y);
  builder_.add_x(x);
  builder_.add_id(id);
  return builder_.Finish();
}

inline const fpacket::PacketPutPlayer *GetPacketPutPlayer(const void *buf) { return flatbuffers::GetRoot<fpacket::PacketPutPlayer>(buf); }

inline bool VerifyPacketPutPlayerBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<fpacket::PacketPutPlayer>(); }

inline void FinishPacketPutPlayerBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<fpacket::PacketPutPlayer> root) { fbb.Finish(root); }

}  // namespace fpacket

#endif  // FLATBUFFERS_GENERATED_PACKETPUTPLAYER_FPACKET_H_
