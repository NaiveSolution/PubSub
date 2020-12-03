#ifndef _FlowControl_H_
#define _FlowControl_H_

#include <dds/core/ddscore.hpp>

namespace tutorial2
{
    class FlowSensorType OSPL_DDS_FINAL
    {
    public:
        int16_t id_;
        float flow_rate_;
        float pressure_;

    public:
        FlowSensorType() :
                id_(0),
                flow_rate_(0.0f),
                pressure_(0.0f) {}

        explicit FlowSensorType(
            int16_t id,
            float flow_rate,
            float pressure) : 
                id_(id),
                flow_rate_(flow_rate),
                pressure_(pressure) {}

        FlowSensorType(const FlowSensorType &_other) : 
                id_(_other.id_),
                flow_rate_(_other.flow_rate_),
                pressure_(_other.pressure_) {}

#ifdef OSPL_DDS_CXX11
        FlowSensorType(FlowSensorType &&_other) : 
                id_(::std::move(_other.id_)),
                flow_rate_(::std::move(_other.flow_rate_)),
                pressure_(::std::move(_other.pressure_)) {}

        FlowSensorType& operator=(FlowSensorType &&_other)
        {
            if (this != &_other) {
                id_ = ::std::move(_other.id_);
                flow_rate_ = ::std::move(_other.flow_rate_);
                pressure_ = ::std::move(_other.pressure_);
            }
            return *this;
        }
#endif

        FlowSensorType& operator=(const FlowSensorType &_other)
        {
            if (this != &_other) {
                id_ = _other.id_;
                flow_rate_ = _other.flow_rate_;
                pressure_ = _other.pressure_;
            }
            return *this;
        }

        bool operator==(const FlowSensorType& _other) const
        {
            return id_ == _other.id_ &&
                flow_rate_ == _other.flow_rate_ &&
                pressure_ == _other.pressure_;
        }

        bool operator!=(const FlowSensorType& _other) const
        {
            return !(*this == _other);
        }

        int16_t id() const { return this->id_; }
        int16_t& id() { return this->id_; }
        void id(int16_t _val_) { this->id_ = _val_; }
        float flow_rate() const { return this->flow_rate_; }
        float& flow_rate() { return this->flow_rate_; }
        void flow_rate(float _val_) { this->flow_rate_ = _val_; }
        float pressure() const { return this->pressure_; }
        float& pressure() { return this->pressure_; }
        void pressure(float _val_) { this->pressure_ = _val_; }
    };

}

#endif /* _FlowControl_H_ */
