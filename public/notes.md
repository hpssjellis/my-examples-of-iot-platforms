    const run = async() =>{        

        console.log("Starting");
        try {
            client.on("message", (topic, message) =>{
                var rfidPayload = JSON.parse(message.toString());
                console.log(rfidPayload);
                var carKeyIn = rfidPayload.carKey;
                var renterIDIn = rfidPayload.renterID;
                var timestampIn = rfidPayload.timestamp;
    
                contract.submitTransaction('openCar', carKeyIn, renterIDIn, timestampIn);
                console.log('Transaction has been submitted');

                
            // This line doesn't run until the server responds to the publish
            await client.end();
            // This line doesn't run until the client has disconnected without error
            console.log("Done");
            });
            await client.subscribe("rfidData");
            console.log("Subscribed")
        } catch (e){
            // Do something about it!
            console.log(e.stack);
            process.exit(2);
        }
    }
    
    client.on("connect", run)








/**
   * Send an MQTT message with new image version details.
   *
   * @param image the image
   * @returns {Promise<void>}
   */
  async notify(image) {
    const options = {};
    if (this.configuration.user) {
      options.username = this.configuration.user;
    }
    if (this.configuration.password) {
      options.password = this.configuration.password;
    }
    const client = await mqtt.connectAsync(this.configuration.url, options);
    return client.publish(this.configuration.topic, JSON.stringify(image));
  }
    
    
    
    
    
