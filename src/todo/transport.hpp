
#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <snd/postypes.hpp>

namespace mojo {

/**
   The transport state needs to be updated at 
   specific times as the transport state must be
   consistant for each "slave" of the transport. A
   slave in this case might be an audio track. Each
   track needs to be using the same state. If RCU is
   used so that the transport state is updated 
   atomically then the update needs to occur when
   there are no readers rather than when the writer
   makes a change.


*/
struct TransportState
{
    double m_speed;
    snd::streampos m_streampos;
    
};


/**
   The transport master uses a RCU class to manage the transport
   so that the transport state can't change between cycles.

   This could be managed by sending transport events to the 
   processing thread so that the transport state is updated 
   in an atomic fashion from that thread. I'm not sure of the 
   all of the advantages of doing it using RCU.



*/
class Transport : public sigc::trackable
{
public:

    Transport();
    virtual ~Transport();

    /**
      The standard stop and play for convenience, play
      really correllates to set_speed(1.0f) and stop to
      set_speed(0.0f).
    */
    void play();
    void stop();
    
    void goto_start();
    void goto_end();
    
    void set_speed(double speed);
    double get_speed() const;
    
    void set_streampos(snd::streampos new_pos);
    snd::streampos get_streampos() const;
    
    /**
       Set an artificial end of stream position, if 
       recording is enabled and the stream position goes 
       past the stream point then the stream end point will
       be updated to reflect the new stream end. If recording
       is not enabled then transport will stop at the stream
       end point.
    */
    void set_streamend(snd::streampos stream_end);
    snd::streampos get_streamend() const;
    
    void set_recording(bool yn);
    bool get_recording() const;
    
    void set_punch(bool yn);
    bool get_punch() const;
    
    void set_looping(bool yn);
    bool get_looping() const;
    
    void set_auto_return(bool yn);
    vool get_auto_return() const;
    
    // void set_stop_on_streampos_change(bool yn);
    
    /**
       This is only emitted when set_streampos is called
       and the new streampos is different that the current
       stream position.
    */
    sigc::signal<void>& signal_streampos_changed() const;
    
    sigc::signal<void>& signal_recording_state_changed() const;
    
    sigc::signal<void>& signal_stream_end_changed() const;
    
    sigc::signal<void>& signal_speed_changed() const;
    
    sigc::signal<void>& signal_punch_changed() const;
    
    sigc::signal<void>& signal_looping_changed() const;
    
    
protected:
}
    
} // namespace mojo
    
#endif // TRANSPORT_HPP
