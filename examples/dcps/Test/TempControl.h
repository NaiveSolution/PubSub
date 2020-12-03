#ifndef _TempControl_H_
#define _TempControl_H_

#include <dds/core/ddscore.hpp>

namespace tutorial
{
    OSPL_ENUM TemperatureScale {
        CELSIUS,
        FAHRENHEIT,
        KELVIN
    };

    class TempSensorType OSPL_DDS_FINAL
    {
    public:
        int16_t id_;
        float temp_;
        float hum_;
        tutorial::TemperatureScale scale_;

    public:
        TempSensorType() :
                id_(0),
                temp_(0.0f),
                hum_(0.0f),
                scale_(OSPL_ENUM_LABEL(tutorial,TemperatureScale,CELSIUS)) {}

        explicit TempSensorType(
            int16_t id,
            float temp,
            float hum,
            tutorial::TemperatureScale scale) : 
                id_(id),
                temp_(temp),
                hum_(hum),
                scale_(scale) {}

        TempSensorType(const TempSensorType &_other) : 
                id_(_other.id_),
                temp_(_other.temp_),
                hum_(_other.hum_),
                scale_(_other.scale_) {}

#ifdef OSPL_DDS_CXX11
        TempSensorType(TempSensorType &&_other) : 
                id_(::std::move(_other.id_)),
                temp_(::std::move(_other.temp_)),
                hum_(::std::move(_other.hum_)),
                scale_(::std::move(_other.scale_)) {}

        TempSensorType& operator=(TempSensorType &&_other)
        {
            if (this != &_other) {
                id_ = ::std::move(_other.id_);
                temp_ = ::std::move(_other.temp_);
                hum_ = ::std::move(_other.hum_);
                scale_ = ::std::move(_other.scale_);
            }
            return *this;
        }
#endif

        TempSensorType& operator=(const TempSensorType &_other)
        {
            if (this != &_other) {
                id_ = _other.id_;
                temp_ = _other.temp_;
                hum_ = _other.hum_;
                scale_ = _other.scale_;
            }
            return *this;
        }

        bool operator==(const TempSensorType& _other) const
        {
            return id_ == _other.id_ &&
                temp_ == _other.temp_ &&
                hum_ == _other.hum_ &&
                scale_ == _other.scale_;
        }

        bool operator!=(const TempSensorType& _other) const
        {
            return !(*this == _other);
        }

        int16_t id() const { return this->id_; }
        int16_t& id() { return this->id_; }
        void id(int16_t _val_) { this->id_ = _val_; }
        float temp() const { return this->temp_; }
        float& temp() { return this->temp_; }
        void temp(float _val_) { this->temp_ = _val_; }
        float hum() const { return this->hum_; }
        float& hum() { return this->hum_; }
        void hum(float _val_) { this->hum_ = _val_; }
        tutorial::TemperatureScale scale() const { return this->scale_; }
        tutorial::TemperatureScale& scale() { return this->scale_; }
        void scale(tutorial::TemperatureScale _val_) { this->scale_ = _val_; }
    };

}

#endif /* _TempControl_H_ */
