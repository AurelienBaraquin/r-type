#pragma once

class Network : public ISystem, public ILoader
{
   public:
    Network();

    ~Network() override;
}
