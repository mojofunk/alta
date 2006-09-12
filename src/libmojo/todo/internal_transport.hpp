
#ifndef MOJO_TRANSPORT_INCLUDED
#define MOJO_TRANSPORT_INCLUDED

namespace mojo {

class Transport {

protected:
        
    double m_speed;
    
    snd::streampos m_streampos;
    
    snd::streampos m_streamend;
    
    snd::streampos m_loop_start;
    
    snd::streampos m_loop_end;
    
    snd::streamoff m_pre_roll;
    
    snd::streamoff m_post_roll;
    
    bool m_recording;
    
    bool m_punch;
    
}
    
} // namespace mojo
    
#endif // MOJO_TRANSPORT_INCLUDED
